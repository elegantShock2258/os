"use client";

import { useEffect, useRef, useState } from "react";
import { parseLogEntries } from "./server/actions/parser";
import styles from "./home.module.sass";
import Log from "@/components/Log/Log";
import { Spinner } from "@/components/ui/spinner";

export default function Page() {
  const [refresh, setRefresh] = useState(false);
  const [logs, setLogs] = useState<string[]>([]);

  let [disconnected, setDisconnected] = useState(false);
  let tries = 2;
  let maxTries = 10;
  let socket: WebSocket;
  function useSocket() {
    if (socket && socket.readyState === WebSocket.OPEN) return;
    socket = new WebSocket("ws://localhost:8080");

    socket.onopen = () => {
      disconnected = false;
      setDisconnected(false);
      tries = 0;
      console.log("connected");
    };
    let disconnectedAction = () => {
      disconnected = true;
      setDisconnected(true);
      console.log("not connected");
      setTimeout(
        () => {
          tries++;
          if (disconnected && tries < maxTries) {
            useSocket();
          }
        },
        1000 * (1 << tries),
      );
    };

    socket.onerror = disconnectedAction;
    socket.onclose = disconnectedAction;

    if (!disconnected) {
      socket.binaryType = "arraybuffer";

      socket.onmessage = async (e) => {
        const parsedMessage = parseLogEntries(e.data);
        if (parsedMessage?.type === "message") {
          const y = [...logs, parsedMessage.message];
          console.log(e.data);
          setLogs(y);
        }
        return () => socket.close();
      };
    }
  }
  useEffect(useSocket, [logs, disconnected]);
  return (
    <div className={`${styles.logcat} ${disconnected ? styles.disable : ""}`}>
      {!disconnected ? (
        <>
          {refresh && <></>}
          {logs.map((log, i) => {
            return <Log log={log} key={i} />;
          })}
        </>
      ) : (
        <div className="w-full h-full flex items-center flex-col justify-center gap-5">
          <div className="flex gap-3 items-center text-[20px]">
            Retrying <Spinner show={disconnected.current} />
          </div>
          use 'yarn run deno-server' to start the server
        </div>
      )}
    </div>
  );
}
