// Low level ATA disk definitions
//
// Copyright (C) 2008  Kevin O'Connor <kevin@koconnor.net>
// Copyright (C) 2002  MandrakeSoft S.A.
//
// This file may be distributed under the terms of the GNU GPLv3 license.

#ifndef __ATA_H
#define __ATA_H

#include "types.h" // u16

// Function definitions
void ata_reset(u16 device);
u16 ata_cmd_data(u16 device, u16 command, u16 count, u16 cylinder
                 , u16 head, u16 sector, u32 lba, u16 segment, u16 offset);
u16 ata_cmd_packet(u16 device, u8 *cmdbuf, u8 cmdlen, u16 header
                   , u32 length, u8 inout, u16 bufseg, u16 bufoff);
u16 cdrom_read(u16 device, u32 lba, u32 count
               , u16 segment, u16 offset, u16 skip);
void ata_detect();

// Global defines -- ATA register and register bits.
// command block & control block regs
#define ATA_CB_DATA  0   // data reg         in/out pio_base_addr1+0
#define ATA_CB_ERR   1   // error            in     pio_base_addr1+1
#define ATA_CB_FR    1   // feature reg         out pio_base_addr1+1
#define ATA_CB_SC    2   // sector count     in/out pio_base_addr1+2
#define ATA_CB_SN    3   // sector number    in/out pio_base_addr1+3
#define ATA_CB_CL    4   // cylinder low     in/out pio_base_addr1+4
#define ATA_CB_CH    5   // cylinder high    in/out pio_base_addr1+5
#define ATA_CB_DH    6   // device head      in/out pio_base_addr1+6
#define ATA_CB_STAT  7   // primary status   in     pio_base_addr1+7
#define ATA_CB_CMD   7   // command             out pio_base_addr1+7
#define ATA_CB_ASTAT 6   // alternate status in     pio_base_addr2+6
#define ATA_CB_DC    6   // device control      out pio_base_addr2+6
#define ATA_CB_DA    7   // device address   in     pio_base_addr2+7

#define ATA_CB_ER_ICRC 0x80    // ATA Ultra DMA bad CRC
#define ATA_CB_ER_BBK  0x80    // ATA bad block
#define ATA_CB_ER_UNC  0x40    // ATA uncorrected error
#define ATA_CB_ER_MC   0x20    // ATA media change
#define ATA_CB_ER_IDNF 0x10    // ATA id not found
#define ATA_CB_ER_MCR  0x08    // ATA media change request
#define ATA_CB_ER_ABRT 0x04    // ATA command aborted
#define ATA_CB_ER_NTK0 0x02    // ATA track 0 not found
#define ATA_CB_ER_NDAM 0x01    // ATA address mark not found

#define ATA_CB_ER_P_SNSKEY 0xf0   // ATAPI sense key (mask)
#define ATA_CB_ER_P_MCR    0x08   // ATAPI Media Change Request
#define ATA_CB_ER_P_ABRT   0x04   // ATAPI command abort
#define ATA_CB_ER_P_EOM    0x02   // ATAPI End of Media
#define ATA_CB_ER_P_ILI    0x01   // ATAPI Illegal Length Indication

// ATAPI Interrupt Reason bits in the Sector Count reg (CB_SC)
#define ATA_CB_SC_P_TAG    0xf8   // ATAPI tag (mask)
#define ATA_CB_SC_P_REL    0x04   // ATAPI release
#define ATA_CB_SC_P_IO     0x02   // ATAPI I/O
#define ATA_CB_SC_P_CD     0x01   // ATAPI C/D

// bits 7-4 of the device/head (CB_DH) reg
#define ATA_CB_DH_DEV0 0xa0    // select device 0
#define ATA_CB_DH_DEV1 0xb0    // select device 1
#define ATA_CB_DH_LBA 0x40    // use LBA

// status reg (CB_STAT and CB_ASTAT) bits
#define ATA_CB_STAT_BSY  0x80  // busy
#define ATA_CB_STAT_RDY  0x40  // ready
#define ATA_CB_STAT_DF   0x20  // device fault
#define ATA_CB_STAT_WFT  0x20  // write fault (old name)
#define ATA_CB_STAT_SKC  0x10  // seek complete
#define ATA_CB_STAT_SERV 0x10  // service
#define ATA_CB_STAT_DRQ  0x08  // data request
#define ATA_CB_STAT_CORR 0x04  // corrected
#define ATA_CB_STAT_IDX  0x02  // index
#define ATA_CB_STAT_ERR  0x01  // error (ATA)
#define ATA_CB_STAT_CHK  0x01  // check (ATAPI)

// device control reg (CB_DC) bits
#define ATA_CB_DC_HD15   0x08  // bit should always be set to one
#define ATA_CB_DC_SRST   0x04  // soft reset
#define ATA_CB_DC_NIEN   0x02  // disable interrupts

// Most mandtory and optional ATA commands (from ATA-3),
#define ATA_CMD_CFA_ERASE_SECTORS            0xC0
#define ATA_CMD_CFA_REQUEST_EXT_ERR_CODE     0x03
#define ATA_CMD_CFA_TRANSLATE_SECTOR         0x87
#define ATA_CMD_CFA_WRITE_MULTIPLE_WO_ERASE  0xCD
#define ATA_CMD_CFA_WRITE_SECTORS_WO_ERASE   0x38
#define ATA_CMD_CHECK_POWER_MODE1            0xE5
#define ATA_CMD_CHECK_POWER_MODE2            0x98
#define ATA_CMD_DEVICE_RESET                 0x08
#define ATA_CMD_EXECUTE_DEVICE_DIAGNOSTIC    0x90
#define ATA_CMD_FLUSH_CACHE                  0xE7
#define ATA_CMD_FORMAT_TRACK                 0x50
#define ATA_CMD_IDENTIFY_DEVICE              0xEC
#define ATA_CMD_IDENTIFY_DEVICE_PACKET       0xA1
#define ATA_CMD_IDENTIFY_PACKET_DEVICE       0xA1
#define ATA_CMD_IDLE1                        0xE3
#define ATA_CMD_IDLE2                        0x97
#define ATA_CMD_IDLE_IMMEDIATE1              0xE1
#define ATA_CMD_IDLE_IMMEDIATE2              0x95
#define ATA_CMD_INITIALIZE_DRIVE_PARAMETERS  0x91
#define ATA_CMD_INITIALIZE_DEVICE_PARAMETERS 0x91
#define ATA_CMD_NOP                          0x00
#define ATA_CMD_PACKET                       0xA0
#define ATA_CMD_READ_BUFFER                  0xE4
#define ATA_CMD_READ_DMA                     0xC8
#define ATA_CMD_READ_DMA_QUEUED              0xC7
#define ATA_CMD_READ_MULTIPLE                0xC4
#define ATA_CMD_READ_SECTORS                 0x20
#define ATA_CMD_READ_VERIFY_SECTORS          0x40
#define ATA_CMD_RECALIBRATE                  0x10
#define ATA_CMD_REQUEST_SENSE                0x03
#define ATA_CMD_SEEK                         0x70
#define ATA_CMD_SET_FEATURES                 0xEF
#define ATA_CMD_SET_MULTIPLE_MODE            0xC6
#define ATA_CMD_SLEEP1                       0xE6
#define ATA_CMD_SLEEP2                       0x99
#define ATA_CMD_STANDBY1                     0xE2
#define ATA_CMD_STANDBY2                     0x96
#define ATA_CMD_STANDBY_IMMEDIATE1           0xE0
#define ATA_CMD_STANDBY_IMMEDIATE2           0x94
#define ATA_CMD_WRITE_BUFFER                 0xE8
#define ATA_CMD_WRITE_DMA                    0xCA
#define ATA_CMD_WRITE_DMA_QUEUED             0xCC
#define ATA_CMD_WRITE_MULTIPLE               0xC5
#define ATA_CMD_WRITE_SECTORS                0x30
#define ATA_CMD_WRITE_VERIFY                 0x3C

#define ATA_IFACE_NONE    0x00
#define ATA_IFACE_ISA     0x00
#define ATA_IFACE_PCI     0x01

#define ATA_TYPE_NONE     0x00
#define ATA_TYPE_UNKNOWN  0x01
#define ATA_TYPE_ATA      0x02
#define ATA_TYPE_ATAPI    0x03

#define ATA_DEVICE_NONE  0x00
#define ATA_DEVICE_HD    0xFF
#define ATA_DEVICE_CDROM 0x05

#define ATA_MODE_NONE    0x00
#define ATA_MODE_PIO16   0x00
#define ATA_MODE_PIO32   0x01
#define ATA_MODE_ISADMA  0x02
#define ATA_MODE_PCIDMA  0x03
#define ATA_MODE_USEIRQ  0x10

#define ATA_TRANSLATION_NONE  0
#define ATA_TRANSLATION_LBA   1
#define ATA_TRANSLATION_LARGE 2
#define ATA_TRANSLATION_RECHS 3

#define ATA_DATA_NO      0x00
#define ATA_DATA_IN      0x01
#define ATA_DATA_OUT     0x02

#endif /* __ATA_H */
