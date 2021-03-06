SUMMARY = "Freescale IMX firmware"
DESCRIPTION = "Freescale IMX firmware such as for the VPU"
SECTION = "base"
LICENSE = "Proprietary"
LIC_FILES_CHKSUM = "file://licenses/vpu/EULA;md5=6469a8514eed615d6bf8c09f41846d8f"

INC_PR = "r4"

SRC_URI = "${FSL_MIRROR}/firmware-imx-${PV}.bin;fsl-eula=true"

inherit fsl-eula-unpack allarch

do_install() {
	install -d ${D}/lib/firmware
    cp -rfv firmware/* ${D}/lib/firmware/
    find ${D}/lib/firmware -type f -exec chmod 644 '{}' ';'

    # Remove files not going to be installed
    find ${D}/lib/firmware/ -name Android.mk -exec rm '{}' ';'
    rm ${D}/lib/firmware/LICENCE.atheros_firmware \
       ${D}/lib/firmware/README
}

PACKAGES += "${PN}-ath6k ${PN}-ar3k"

FILES_${PN}-ath6k = "/lib/firmware/ath6k/*"
FILES_${PN}-ar3k  = "/lib/firmware/ar3k/*"

python populate_packages_prepend() {
    vpudir = bb.data.expand('/lib/firmware/vpu', d)
    do_split_packages(d, vpudir, '^vpu_fw_([^_]*).*\.bin',
                      output_pattern='firmware-imx-vpu-%s',
                      description='Freescale IMX Firmware %s',
                      extra_depends='',
                      prepend=True)

    sdmadir = bb.data.expand('/lib/firmware/sdma', d)
    do_split_packages(d, sdmadir, '^sdma-([^-]*).*\.bin',
                      output_pattern='firmware-imx-sdma-%s',
                      description='Freescale IMX Firmware %s',
                      extra_depends='',
                      prepend=True)
}

PACKAGES_DYNAMIC = "${PN}-vpu-* ${PN}-sdma-*"
