"use client";
import { useEffect, useRef, useState } from "react";
import styles from "./kmalloc.modules.sass";
import { parseLogEntries } from "../server/actions/parser";

export default function page() {
  let kmap = useRef<string>("");
  let [refresh, setRefresh] = useState(false);
  useEffect(() => {
    const socket = new WebSocket("ws://localhost:8080");
    socket.binaryType = "arraybuffer";

    socket.onmessage = async (e) => {
      const parsedMessage = parseLogEntries(e.data);
      if (parsedMessage?.type === "kmalloc") {
        kmap.current = parsedMessage.bitmap;
        setRefresh(!refresh);
      }
      return () => socket.close();
    };
  }, []);

  return (
    <>
      {refresh && <></>}
      {kmap.current}
      {/* <Kmap map={kmap.current} /> */}
    </>
  );
}
