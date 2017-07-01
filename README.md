# Override able traffic light system
A [WATCH_DOGS](http://store.steampowered.com/app/243470/Watch_Dogs/) like smartphone controlled traffic light system, which is designed to give service vehicles a priority.

# Usage

## Arduino
1. The pins are `5-10` in order of `Red-Yellow-Green-Red-Yellow-Green`.
2. Pins `2` and `3` are `RX` and `TX` for `HC05`-like bluetooth device. 
3. Change the password as required.
4. Upload `SmartTrafficLight.ino` to Arduino board.

## Android
1. Open project using android studio.
2. Build and deploy APK to any bluetooth enabled android device.
