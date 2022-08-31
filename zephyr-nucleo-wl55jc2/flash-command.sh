#bin/bash
/usr/bin/openocd -s /usr/local/share/openocd/scripts/interface -s /usr/local/share/openocd/scripts/target -f stlink.cfg -f stm32wlx.cfg '-c init' '-c targets' -c 'reset halt' -c 'flash write_image erase /home/ted/projects-sandbox/workspace-zephyr-sdk/zephyr/samples/hello_world/build/zephyr/zephyr.hex' -c 'reset halt' -c 'verify_image /home/ted/projects-sandbox/workspace-zephyr-sdk/zephyr/samples/hello_world/build/zephyr/zephyr.hex' -c 'reset run' -c shutdown
exit 0
