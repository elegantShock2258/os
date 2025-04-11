import * as fs from "fs";
import * as path from "path";

type LogEntry =
  | { type: "message"; message: string }
  | {
      type: "framebuffer";
      title: string;
      height: number;
      width: number;
      data: Uint8Array;
    };

// export function parseLogEntries(buffer: Uint8Array): LogEntry[] {
//   const entries: LogEntry[] = [];

//   let i = 0;
//   const decoder = new TextDecoder();

//   while (i < buffer.length) {
//     // Look for the next [LOG]: start
//     const startIndex = buffer.indexOf(0x5b /* [ */, i); // look for '['
//     if (startIndex === -1 || decoder.decode(buffer.slice(startIndex, startIndex + 7)) !== '[LOG]:') {
//       break;
//     }

//     i = startIndex;

//     // Try to read next few hundred characters to see if it's an FB or message
//     const lookahead = decoder.decode(buffer.slice(i, i + 200));

//     if (lookahead.startsWith('[LOG]: [FB]:')) {
//       const fbMatch = lookahead.match(/^\[LOG\]: \[FB\]: ([^\s]+) (\d+)x(\d+)/);
//       if (!fbMatch) break;

//       const [, title, heightStr, widthStr] = fbMatch;
//       const height = parseInt(heightStr, 10);
//       const width = parseInt(widthStr, 10);
//       const pixelCount = height * width;

//       const header = `[LOG]: [FB]: ${title} ${height}x${width}`;
//       const headerBytes = new TextEncoder().encode(header);
//       const dataStart = i + headerBytes.length;

//       const fbData = buffer.slice(dataStart, dataStart + pixelCount);
//       entries.push({
//         type: 'framebuffer',
//         title,
//         height,
//         width,
//         data: fbData,
//       });

//       i = dataStart + pixelCount;
//     } else {
//       // Just a regular log message: find end of this message
//       const nextLogStart = buffer.indexOf(0x5b /* [ */, i + 7);
//       const end = nextLogStart === -1 ? buffer.length : nextLogStart;

//       const logMessage = decoder.decode(buffer.slice(i + 7, end)).trim();
//       entries.push({
//         type: 'message',
//         message: logMessage,
//       });

//       i = end;
//     }
//   }

//   return entries;
// }

// export type LogEntry =
//   | { type: 'message'; message: string }
//   | { type: 'framebuffer'; title: string; height: number; width: number; data: string };

export function parseLogEntries(buffer: string): LogEntry[] {
  const entries: LogEntry[] = [];
  let i = 0;

  while (i < buffer.length) {
    const startIndex = buffer.indexOf("[LOG]:", i);
    if (startIndex === -1) break;

    const rest = buffer.slice(startIndex);

    if (rest.startsWith("[LOG]: [FB]:")) {
      const fbMatch = rest.match(/^\[LOG\]: \[FB\]: ([^\s]+) (\d+)x(\d+)/);
      if (!fbMatch) break;

      const [, title, heightStr, widthStr] = fbMatch;
      const height = parseInt(heightStr, 10);
      const width = parseInt(widthStr, 10);
      const pixelCount = height * width;

      const header = `[LOG]: [FB]: ${title} ${height}x${width}`;
      const headerLength = header.length;

      const dataStart = startIndex + headerLength;
      const dataEnd = dataStart + pixelCount;

      const data = buffer.slice(dataStart, dataEnd);

      entries.push({
        type: "framebuffer",
        title,
        height,
        width,
        data,
      });

      i = dataEnd;
    } else {
      const nextLogIndex = buffer.indexOf("[LOG]:", startIndex + 1);
      const end = nextLogIndex === -1 ? buffer.length : nextLogIndex;

      const message = buffer.slice(startIndex + "[LOG]:".length, end).trim();

      entries.push({
        type: "message",
        message,
      });

      i = end;
    }
  }

  return entries;
}
