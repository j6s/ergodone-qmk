KEYMAP_NAME=j6s-default

QMK_DIR=${CURDIR}/qmk_firmware
FIRMWARE_HEX=${QMK_DIR}/.build/ergodone_${KEYMAP_NAME}.hex

TKG_DIR=${CURDIR}/tkg_toolkit
HID_BOOTLOADER=${TKG_DIR}/linux/bin/hid_bootloader_cli


# Shortcuts for humans
# - build / rebuild for building / rebuilding
# - flash for building + flashing to keyboard
# - reflash for rebuilding + flashing to keyboard
# - clean to remove previously built firmwares
# - fullclean to also remove qmk firmware. This requires 
#   recloning the source code on next build. Use carefully,
#   especially if you are not on a network connection.
build: ${FIRMWARE_HEX}
rebuild: | clean build
flash: ${TKG_DIR} build
	@cat bootloader-mode-instructions.txt
	sudo ${HID_BOOTLOADER} -w -v -mmcu=atmega32u4 ${FIRMWARE_HEX}
reflash: | clean flash
clean:
	rm -f ${FIRMWARE_HEX}
fullclean:
	rm -Rf ${QMK_DIR}


${QMK_DIR}:
	git clone https://github.com/qmk/qmk_firmware.git ${QMK_DIR} --recursive
	cd ${QMK_DIR}/keyboards/ergodone/keymaps && ln -s ../../../../ ${KEYMAP_NAME}

${TKG_DIR}:
	git clone https://github.com/kairyu/tkg-toolkit ${TKG_DIR} --recursive


# See qmk_firmware/util/docker_build.sh
# This is a slightly modified version of that script, that
# mounts this folder into the container instead of only
# qmk_firmware. That way the symlink to the keymap works
# correctly.
${FIRMWARE_HEX}: | ${QMK_DIR}
	docker run --rm -it \
		--privileged -v /dev:/dev \
		--user $$(id -u):$$(id -g) \
		-v "$$(pwd):/build" \
		-w /build/qmk_firmware \
		-e ALT_GET_KEYBOARDS=true \
		qmkfm/base_container \
		make "ergodone:${KEYMAP_NAME}"

