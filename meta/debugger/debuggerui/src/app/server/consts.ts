export let QEMU_HOST = process.env.QEMU_HOST;
export let QEMU_PORT = process.env.QEMU_PORT;
export let DENO_WEB_SERVER_HOST = process.env.DENO_WEB_SERVER_HOST;
export let DENO_WEB_SERVER_PORT = process.env.DENO_WEB_SERVER_PORT;
export let FRONTEND_HOST = process.env.FRONTEND_HOST;
export let FRONTEND_PORT = process.env.FRONTEND_PORT;

export function CheckEnv() {
  const envVars = {
    QEMU_HOST,
    QEMU_PORT,
    DENO_WEB_SERVER_HOST,
    DENO_WEB_SERVER_PORT,
    FRONTEND_HOST,
    FRONTEND_PORT,
  };
  if (typeof Deno !== "undefined" && typeof Deno.env?.get === "function") {
    QEMU_HOST = Deno.env.get("QEMU_HOST") ?? null;
    QEMU_PORT = Deno.env.get("QEMU_PORT") ?? null;
    DENO_WEB_SERVER_HOST = Deno.env.get("DENO_WEB_SERVER_HOST") ?? null;
    DENO_WEB_SERVER_PORT = Deno.env.get("DENO_WEB_SERVER_PORT") ?? null;
    FRONTEND_HOST = Deno.env.get("FRONTEND_HOST") ?? null;
    FRONTEND_PORT = Deno.env.get("FRONTEND_PORT") ?? null;
  }

  for (const [key, value] of Object.entries(envVars)) {
    if (value === undefined || value === null || value === "") {
      console.warn(`⚠️ Warning: Environment variable ${key} is not specified.`);
    } else {
      console.log(`${key} = ${value}`);
    }
  }
}
