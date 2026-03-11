# Modified Advanced Charging System (MACS) main script (main.py)
#
#
# Copyright (C) 2025-Present Arijit Kumar Das <arijitkdgit.official@gmail.com>
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program. If not, see <https://www.gnu.org/licenses/>.


from machine import Pin
import time
import select
import sys


HIGH = 1
LOW = 0
START = "1"
STOP = "0"
COM_TOUT = 2
RELAX_TOUT = 1
DEV_NAME = "MACS001"


def fuse_input(timeout_s):
    if (select.select([sys.stdin], [], [], timeout_s)[0]):
        return sys.stdin.readline().strip()
    return None


def driver(relay, charge_led):
    command = fuse_input(COM_TOUT)

    if (command == STOP and relay.value() == LOW):
        relay.on()
        charge_led.off()
        return 0

    elif (command == START and relay.value() == HIGH):
        relay.off()
        charge_led.on()
        return 1
    
    return -1


def main():
    relay = Pin(0, Pin.OUT)
    pico_led = Pin(25, Pin.OUT)
    pico_led.on()

    while (1):
        print (DEV_NAME)
        stat = driver(relay, pico_led)

        if (stat == LOW):
            time.sleep(RELAX_TOUT)

        elif (stat == HIGH):
            time.sleep(RELAX_TOUT)


if (__name__ == "__main__"):
    main()
