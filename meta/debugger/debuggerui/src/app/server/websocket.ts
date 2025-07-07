// deno run --allow-net serialProxy.ts

import {
  CheckEnv,
  DENO_WEB_SERVER_HOST,
  DENO_WEB_SERVER_PORT,
  QEMU_HOST,
  QEMU_PORT,
} from "./consts.ts";

CheckEnv();
const clients = new Set<WebSocket>();

// Start WebSocket server to connect to frontend
Deno.serve(
  { port: DENO_WEB_SERVER_PORT, host: DENO_WEB_SERVER_HOST },
  async (req) => {
    const { socket, response } = Deno.upgradeWebSocket(req);
    socket.onopen = () => {
      console.log("[WS] Client connected");
      clients.add(socket);
    };
    socket.onclose = () => {
      console.log("[WS] Client disconnected");
      clients.delete(socket);
    };
    return response;
  },
);

// Start TCP server to isten to qemu
const listener = Deno.listen({ port: QEMU_PORT, host: QEMU_HOST });
console.log(
  `✅ TCP server listening on port https://${QEMU_HOST}:${QEMU_PORT}`,
);
console.log(
  `✅ WebSocket server listening on ws://${DENO_WEB_SERVER_HOST}:${DENO_WEB_SERVER_PORT}`,
);

for await (const conn of listener) {
  console.log("[TCP] QEMU connected");
  handleTCP(conn).catch((err) => {
    console.error("[TCP] Error:", err);
  });
}

// 🔧 Buffer and parse |...| wrapped messages
async function handleTCP(conn: Deno.Conn) {
  const decoder = new TextDecoder();
  let textBuffer = ""; // Collects raw text between packets

  const buffer = new Uint8Array(1024);

  while (true) {
    const bytesRead = await conn.read(buffer);
    if (bytesRead === null) {
      console.log("[TCP] QEMU disconnected");
      break;
    }

    const chunk = decoder.decode(buffer.subarray(0, bytesRead));
    textBuffer += chunk;

    let start: number;
    let end: number;

    // Process all full |...| messages
    while (
      (start = textBuffer.indexOf("|")) !== -1 &&
      (end = textBuffer.indexOf("|", start + 1)) !== -1
    ) {
      const message = textBuffer.slice(start + 1, end);

      for (const ws of clients) {
        if (ws.readyState === WebSocket.OPEN) {
          ws.send(message);
          console.log(message);
        }
      }

      textBuffer = textBuffer.slice(end + 1);
    }
  }
}
