#!/usr/bin/env python3

# Starts a server on port 30303
# and periodically broadcasts color
# information to every connected client

import asyncio as aio

class RgbServer(object):
    def __init__(self, loop=None):
        self.loop= aio.get_event_loop() if loop is None else loop

        self.event_sinks= list()

        self.coro= aio.start_server(
            self.handle_client,
            None,
            30303,
            loop= self.loop
        )

        self.server= self.loop.run_until_complete(self.coro)

        self.update_task= aio.Task(self.update_color())
        self.updater= self.loop.run_until_complete(self.update_task)

    def run(self):
        try:
            self.loop.run_forever()
        except KeyboardInterrupt:
            pass

        self.server.close()
        self.update_task.cancel()

        self.loop.run_until_complete(self.server.wait_closed())
        self.loop.close()

    async def update_color(self):
        hue= 0

        while True:
            print(
                'Broadcasting hue {} to {} clients'.format(
                    int(hue),
                    len(self.event_sinks)
                )
            )

            for ev in self.event_sinks:
                await ev.put(int(hue))

            hue= (hue + 25) % 767

            await aio.sleep(0.25)

    async def handle_client(self, reader, writer):
        event_source= aio.Queue(8, loop=self.loop)

        self.event_sinks.append(event_source)

        while True:
            event= await event_source.get()

            try:
                writer.write('{}\n'.format(event).encode('utf-8'))
                await writer.drain()
            except ConnectionError:
                self.event_sinks.remove(event_source)
                break

srv= RgbServer()
srv.run()
