# Pebble Bathroom Mac OSX 10.10+ Widget

Shows whether the men's bathroom by the snack kitchen is occupied or vacant.

Bathroom vacant:
![bathroom vacant screenshot](screenshots/vacant.png?raw=true)

Bathroom occupied:
![bathroom occupied screenshot](screenshots/occupied.png?raw=true)

Error communicating with hardware:
![bathroom error screenshot](screenshots/unknown.png?raw=true)

The widget polls the Arduino monitoring the bathroom lock every 3 seconds.

## Inspiration
The idea for an OSX menu bar widget came from a similar bathroom status project called [Is the Toilet Free?](http://madebymany.com/blog/is-the-toilet-free).

## Installation

1. Grab a binary from the [Releases page](https://github.com/pebble/toilet-time/releases).
2. Add it to your Applications folder.
3. Double click to launch it.

### Automatically launch the app at login

Open System Preferences, Users & Groups, Login Items and either drag the app binary to the list or click the "+" icon and browse for the app binary.

![launch at login screenshot](screenshots/login.png?raw=true)

## Ideas for contributions

- Support updating the bathroom status via websockets eventually when the hardware/backend provides it
- Improve icon design
- Adjust icon colors programmatically based on whether light or dark OSX theme is being used
- Support monitoring multiple bathrooms once additional hardware is installed
