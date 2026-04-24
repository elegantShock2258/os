import { HoverCard } from "@/components/ui/hover-card";
import { HoverCardContent, HoverCardTrigger } from "@radix-ui/react-hover-card";
import styles from "./KmapCell.modules.sass";
//TODO: add memory addr details for the block so you can analyse the memory
export function KmapCell({ busy }: { busy: "0" | "1" }) {
  return (
    <HoverCard>
      <HoverCardTrigger>
        <div>{busy}</div>
      </HoverCardTrigger>
      <HoverCardContent>
        info about the cell, starting addr, ending addr onclick have a little
        zoom in animation and show all the data within the block
      </HoverCardContent>
    </HoverCard>
  );
}
