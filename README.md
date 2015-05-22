# Toilet-Time

Get the status of a bathroom lock on your wrist so you know when it is toilet
time.

This was developed and iterated to solve bathroom queue issues at Pebble HQ and
was later evolved into a public example application for presentation at
JSConf 2015.

This project is made up of three components: An Arduino firmware, a watchapp,
and a NodeJs server.

The Arduino that pushes the status of a lock-attached switch to
a NodeJS Pebble Timeline server. This server in turn pushes Timeline Pins to
the "toilet-time" Topic. Watches with the watchapp installed subscribe to the
"toilet-time" topic and get updates on the lock status.

## Requirements 

  * Arduino-compatible dev board.
  * Arduino-compatible Ethernet Shield
  * Switch of some kind
  * NodeJS capable web server
  * Pebble Time / Pebble Time Steel watches
  * Pebble SDK installed
  * Pebble Timeline API Key

## Setup

  1. Install server dependencies

      ```
      cd timeline-server
      npm install
      ```

  2. Start Server

      ```
      API_KEY="YOUR_API_KEY" npm start
      ```

  3. Adjust Arduino code to point at your server:

      ```
      cd lock-status
      sed 's/__HOST__/YOUR-DOMAIN.com/g' -i lock-status.ino
      ```

  4. Upload firmware to Arduino

      ```
      arduino --upload lock-status.ino
      ```

  5. Connect switch to +5v and Analog Input 2 on Arduino

  6. Attach switch as such that it makes a circuit when door is locked

  7. Build Watchapp

      ```
      cd watch-client
      pebble build
      ```

  8. Install Watchapp

      ```
      pebble install
      ```

  9. Enjoy watching your Timeline update when the lock status changes :D

## Notes

Does hacking on stuff like this sound fun? Come join our team!

[ https://getpebble.com/jobs ]
