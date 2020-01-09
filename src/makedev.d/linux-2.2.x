# This file is written almost directly from the devices.txt file provided in
# the Documentation/ subdirectory of the Linux kernel source tree.

c 640 root     kmem      1   1  1   1 mem
c 640 root     kmem      1   2  1   1 kmem
c 666 root     root      1   3  1   1 null
c 640 root     kmem      1   4  1   1 port
c 666 root     root      1   5  1   1 zero
c 666 root     root      1   7  1   1 full
c 644 root     root      1   8  1   1 random
c 644 root     root      1   9  1   1 urandom

b 660 root     disk      1   0  1 128 ram%d
b 660 root     disk      1 250  1   1 initrd

c 666 root     tty       2   0  1  16 ptyp%x
c 666 root     tty       2  16  1  16 ptyq%x
c 666 root     tty       2  32  1  16 ptyr%x
c 666 root     tty       2  48  1  16 ptys%x
c 666 root     tty       2  64  1  16 ptyt%x
c 666 root     tty       2  80  1  16 ptyu%x
c 666 root     tty       2  96  1  16 ptyv%x
c 666 root     tty       2 112  1  16 ptyw%x
c 666 root     tty       2 128  1  16 ptyx%x
c 666 root     tty       2 144  1  16 ptyy%x
c 666 root     tty       2 160  1  16 ptyz%x
c 666 root     tty       2 176  1  16 ptya%x
c 666 root     tty       2 192  1  16 ptyb%x
c 666 root     tty       2 208  1  16 ptyc%x
c 666 root     tty       2 224  1  16 ptyd%x
c 666 root     tty       2 240  1  16 ptye%x

b 660 root     floppy    2   0  1   4 fd%d 0
b 660 root     floppy    2 128  1   4 fd%d 4

b 660 root     floppy    2   4  1   4 fd%dd360  0
b 660 root     floppy    2  20  1   4 fd%dh360  0
b 660 root     floppy    2  48  1   4 fd%dh410  0
b 660 root     floppy    2  64  1   4 fd%dh420  0
b 660 root     floppy    2  24  1   4 fd%dh720  0
b 660 root     floppy    2  80  1   4 fd%dh880  0
b 660 root     floppy    2   8  1   4 fd%dh1200 0
b 660 root     floppy    2  40  1   4 fd%dh1440 0
b 660 root     floppy    2  56  1   4 fd%dh1476 0
b 660 root     floppy    2  72  1   4 fd%dh1494 0
b 660 root     floppy    2  92  1   4 fd%dh1660 0

b 660 root     floppy    2  12  1   4 fd%du360  0
b 660 root     floppy    2  16  1   4 fd%du720  0
b 660 root     floppy    2 120  1   4 fd%du800  0
b 660 root     floppy    2  52  1   4 fd%du820  0
b 660 root     floppy    2  68  1   4 fd%du830  0
b 660 root     floppy    2  84  1   4 fd%du1040 0
b 660 root     floppy    2  88  1   4 fd%du1120 0
b 660 root     floppy    2  28  1   4 fd%du1440 0
b 660 root     floppy    2 124  1   4 fd%du1660 0
b 660 root     floppy    2  44  1   4 fd%du1680 0
b 660 root     floppy    2  60  1   4 fd%du1722 0
b 660 root     floppy    2  76  1   4 fd%du1743 0
b 660 root     floppy    2  96  1   4 fd%du1760 0
b 660 root     floppy    2 116  1   4 fd%du1840 0
b 660 root     floppy    2 100  1   4 fd%du1920 0
b 660 root     floppy    2  32  1   4 fd%du2880 0
b 660 root     floppy    2 104  1   4 fd%du3200 0
b 660 root     floppy    2 108  1   4 fd%du3520 0
b 660 root     floppy    2 112  1   4 fd%du3840 0

b 660 root     floppy    2 132  1   4 fd%dd360  4
b 660 root     floppy    2 148  1   4 fd%dh360  4
b 660 root     floppy    2 176  1   4 fd%dh410  4
b 660 root     floppy    2 192  1   4 fd%dh420  4
b 660 root     floppy    2 152  1   4 fd%dh720  4
b 660 root     floppy    2 208  1   4 fd%dh880  4
b 660 root     floppy    2 136  1   4 fd%dh1200 4
b 660 root     floppy    2 168  1   4 fd%dh1440 4
b 660 root     floppy    2 184  1   4 fd%dh1476 4
b 660 root     floppy    2 200  1   4 fd%dh1494 4
b 660 root     floppy    2 220  1   4 fd%dh1660 4

b 660 root     floppy    2 140  1   4 fd%du360  4
b 660 root     floppy    2 144  1   4 fd%du720  4
b 660 root     floppy    2 248  1   4 fd%du800  4
b 660 root     floppy    2 180  1   4 fd%du820  4
b 660 root     floppy    2 196  1   4 fd%du830  4
b 660 root     floppy    2 212  1   4 fd%du1040 4
b 660 root     floppy    2 216  1   4 fd%du1120 4
b 660 root     floppy    2 156  1   4 fd%du1440 4
b 660 root     floppy    2 252  1   4 fd%du1660 4
b 660 root     floppy    2 172  1   4 fd%du1680 4
b 660 root     floppy    2 188  1   4 fd%du1722 4
b 660 root     floppy    2 204  1   4 fd%du1743 4
b 660 root     floppy    2 224  1   4 fd%du1760 4
b 660 root     floppy    2 244  1   4 fd%du1840 4
b 660 root     floppy    2 228  1   4 fd%du1920 4
b 660 root     floppy    2 160  1   4 fd%du2880 4
b 660 root     floppy    2 232  1   4 fd%du3200 4
b 660 root     floppy    2 236  1   4 fd%du3520 4
b 660 root     floppy    2 240  1   4 fd%du3840 4

b 660 root     floppy    2   4  1   4 fd%dCompaQ 0
b 660 root     floppy    2 132  1   4 fd%dCompaQ 4

c 666 root     tty       3   0  1  16 ttyp%x
c 666 root     tty       3  16  1  16 ttyq%x
c 666 root     tty       3  32  1  16 ttyr%x
c 666 root     tty       3  48  1  16 ttys%x
c 666 root     tty       3  64  1  16 ttyt%x
c 666 root     tty       3  80  1  16 ttyu%x
c 666 root     tty       3  96  1  16 ttyv%x
c 666 root     tty       3 112  1  16 ttyw%x
c 666 root     tty       3 128  1  16 ttyx%x
c 666 root     tty       3 144  1  16 ttyy%x
c 666 root     tty       3 160  1  16 ttyz%x
c 666 root     tty       3 176  1  16 ttya%x
c 666 root     tty       3 192  1  16 ttyb%x
c 666 root     tty       3 208  1  16 ttyc%x
c 666 root     tty       3 224  1  16 ttyd%x
c 666 root     tty       3 240  1  16 ttye%x

b 660 root     disk      3   0  1  64 hda
b 660 root     disk      3  64  1  64 hdb

c 600 root     root      4   0  1   1 systty
c 600 root     tty       4   0  1  64 tty%d
c 660 root     uucp      4  64  1 192 ttyS%d

c 666 root     root      5   0  1   1 tty
c 600 root     root      5   1  1   1 console
c 666 root     root      5   2  1   1 ptmx
c 660 root     uucp      5  64  1 192 cua%d

c 660 root     lp        6   0  1   4 lp%d

c 620 root     tty       7   0  1  64 vcs
c 620 root     tty       7 128  1  64 vcsa

b 660 root     disk      7   0  1  16 loop%d

b 660 root     disk      8   0  1  16 sda
b 660 root     disk      8  16  1  16 sdb
b 660 root     disk      8  32  1  16 sdc
b 660 root     disk      8  48  1  16 sdd
b 660 root     disk      8  64  1  16 sde
b 660 root     disk      8  80  1  16 sdf
b 660 root     disk      8  96  1  16 sdg
b 660 root     disk      8 112  1  16 sdh
b 660 root     disk      8 128  1  16 sdi
b 660 root     disk      8 144  1  16 sdj
b 660 root     disk      8 160  1  16 sdk
b 660 root     disk      8 176  1  16 sdl
b 660 root     disk      8 192  1  16 sdm
b 660 root     disk      8 208  1  16 sdn
b 660 root     disk      8 224  1  16 sdo
b 660 root     disk      8 240  1  16 sdp

c 660 root     disk      9   0  1  32 st%d
c 660 root     disk      9  32  1  32 st%dl
c 660 root     disk      9  64  1  32 st%dm
c 660 root     disk      9  96  1  32 st%da
c 660 root     disk      9 128  1  32 nst%d
c 660 root     disk      9 160  1  32 nst%dl
c 660 root     disk      9 192  1  32 nst%dm
c 660 root     disk      9 224  1  32 nst%da

b 660 root     disk      9   0  1  32 md%d

c 660 root     root     10   0  1   1 logibm
c 660 root     root     10   1  1   1 psaux
c 660 root     root     10   2  1   1 inportbm
c 660 root     root     10   3  1   1 atibm
c 660 root     root     10   4  1   1 jbm
c 660 root     root     10   4  1   1 amigamouse
c 660 root     root     10   5  1   1 atarimouse
c 660 root     root     10   6  1   1 sunmouse
c 660 root     root     10   7  1   1 amigamouse1
c 660 root     root     10   8  1   1 smouse
c 660 root     root     10   9  1   1 pc110pad
c 660 root     root     10  10  1   1 adbmouse
c 660 root     root     10  11  1   1 vrtpanel

c 660 root     root     10 128  1   1 beep
c 660 root     root     10 129  1   1 modreq
c 660 root     root     10 130  1   1 watchdog
c 660 root     root     10 131  1   1 temperature
c 660 root     root     10 132  1   1 hwtrap
c 660 root     root     10 133  1   1 exttrp
c 660 root     sys      10 134  1   1 apm_bios
c 664 root     root     10 135  1   1 rtc
# Where did 136, 137, and 138 go?
c 660 root     root     10 139  1   1 openprom
c 660 root     root     10 140  1   1 relay8
c 660 root     root     10 141  1   1 relay16
c 660 root     root     10 142  1   1 msr
c 660 root     root     10 143  1   1 pciconf
c 660 root     root     10 144  1   1 nvram
c 660 root     root     10 145  1   1 hfmodem
c 660 root     root     10 146  1   1 graphics
c 660 root     root     10 147  1   1 opengl
c 660 root     root     10 148  1   1 gfx
c 666 root     sys      10 149  1   1 input/mouse
c 660 root     root     10 150  1   1 input/keyboard
c 660 root     root     10 151  1   1 led
# Where did 152 go?
c 660 root     root     10 153  1   1 mergemem
c 660 root     root     10 154  1   1 pmu
c 660 root     root     10 155  1   1 isictl
c 660 root     root     10 156  1   1 lcd
c 660 root     root     10 157  1   1 ac
c 660 root     root     10 158  1   1 nwbutton
c 660 root     root     10 159  1   1 nwdebug
c 660 root     root     10 160  1   1 nwflash
c 660 root     root     10 161  1   1 userdma
c 660 root     root     10 162  1   1 smbus
c 660 root     root     10 163  1   1 lik
c 660 root     root     10 164  1   1 ipmo
c 660 root     root     10 165  1   1 vmmon
c 660 root     root     10 166  1   1 i2o/ctl
c 660 root     root     10 167  1   1 specialix_sxctl
c 660 root     root     10 168  1   1 tcldrv
c 660 root     root     10 169  1   1 specialix_rioctl
c 660 root     root     10 170  1   1 smapi
c 660 root     root     10 171  1   1 srripc
c 660 root     root     10 172  1   1 usemacclone
c 660 root     root     10 173  1   1 ipmikcs
c 660 root     root     10 174  1   1 uctrl
c 664 root     root     10 175  1   1 agpgart
c 660 root     root     10 176  1   1 gtrsc
c 660 root     root     10 177  1   1 cbm
c 660 root     root     10 178  1   1 jsflash
c 660 root     root     10 179  1   1 xsvc
c 660 root     root     10 180  1   1 vrbuttons

c 660 root     root     11   0  1   1 kbd
b 660 root     disk     11   0  1  32 sr%d

c 660 root     disk     12   2  1   1 ntpqic11
c 660 root     disk     12   3  1   1 tpqic11
c 660 root     disk     12   4  1   1 ntpqic24
c 660 root     disk     12   5  1   1 tpqic24
c 660 root     disk     12   6  1   1 ntpqic120
c 660 root     disk     12   7  1   1 tpqic120
c 660 root     disk     12   8  1   1 ntpqic150
c 660 root     disk     12   9  1   1 tpqic150

b 660 root     root     12   0  1   8 dos_cd%d

# These are obsolete!
# c 660 root     sys      13   0  1   1 pcmixer
# c 660 root     sys      13   1  1   1 pcsp
# c 660 root     sys      13   4  1   1 pcaudio
# c 660 root     sys      13   5  1   1 pcsp16r

b 660 root     disk     13   0  1  64 xda
b 660 root     disk     13  64  1  64 xdb

c 600 root     sys      14   0  1   1 mixer
c 666 root     sys      14   1  1   1 sequencer
c 600 root     sys      14   2  1   1 midi00
c 600 root     sys      14   3  1   1 dsp
c 600 root     sys      14   4  1   1 audio
# Where did 5 go?
c 644 root     sys      14   6  1   1 sndstat
c 600 root     sys      14   7  1   1 audioctl
c 600 root     sys      14   8  1   1 sequencer2

c 600 root     sys      14  16  1   1 mixer1
c 600 root     sys      14  17  1   1 patmgr0
c 600 root     sys      14  18  1   1 midi01
c 600 root     sys      14  19  1   1 dsp1
c 600 root     sys      14  20  1   1 audio1

c 600 root     sys      14  33  1   1 patmgr1
c 600 root     sys      14  34  1   1 midi02
c 600 root     sys      14  50  1   1 midi03

b 660 root     root     14   0  1  64 dos_hda
b 660 root     root     14  64  1  64 dos_hdb
b 660 root     root     14 128  1  64 dos_hdc
b 660 root     root     14 192  1  64 dos_hdd

c 600 root     root     15   0  1 128 js%d
c 660 root     sys      15 128  1 128 djs%d

b 660 root     disk     15   0  1   1 sonycd

c 660 root     root     16   0  1   1 gs4500
b 660 root     disk     16   0  1   1 gscd

c 660 root     uucp     17   0  1  16 ttyH%d
b 660 root     disk     17   0  1   1 optcd

c 660 root     uucp     18   0  1  16 cuh%d
b 660 root     disk     18   0  1   1 sjcd

c 660 root     uucp     19   0  1  33 ttyC%d
b 660 root     root     19   0  1   8 double%d
b 660 root     root     19 128  1   8 cdouble%d

c 660 root     uucp     20   0  1  32 cub%d
b 660 root     disk     20   0  1   1 hitcd

c 600 root     sys      21   0  1  32 sg%d
b 660 root     root     21   0  1  64 mfma
b 660 root     root     21  64  1  64 mfmb

c 660 root     uucp     22   0  1  32 ttyD%d
b 660 root     disk     22   0  1  64 hdc
b 660 root     disk     22  64  1  64 hdd

c 660 root     uucp     23   0  1  32 cud%d
b 660 root     disk     23   0  1   1 mcd

c 660 root     uucp     24   0  1 256 ttyE%d
b 660 root     disk     24   0  1   1 cdu535

c 660 root     uucp     25   0  1 256 cue%d
b 660 root     disk     25   0  1   4 sbpcd%d 0

c 660 root     sys      26   0  1   1 wvisfgrab
b 660 root     disk     26   0  1   4 sbpcd%d 4

c 660 root     disk     27   0  1   4 qft%d
c 660 root     disk     27   4  1   4 nqft%d
c 660 root     disk     27  16  1   4 zqft%d
c 660 root     disk     27  20  1   4 nzqft%d
c 660 root     disk     27  32  1   4 rawqft%d
c 660 root     disk     27  36  1   4 nrawqft%d
b 660 root     disk     27   0  1   4 sbpcd%d 8

c 600 root     sys      28   0  1   4 staliomem%d
c 660 root     daemon   28   0  1   4 slm%d
b 660 root     disk     28   0  1   4 sbpcd%d 12

# This next set's commented out because it conflicts with the Apple Desktop
# Bus driver, which appears to be the more correct of the two.
# b 660 root     root     28   0  1  16 ada
# b 660 root     root     28  16  1  16 adb
# b 660 root     root     28  32  1  16 adc
# b 660 root     root     28  48  1  16 add
# b 660 root     root     28  64  1  16 ade
# b 660 root     root     28  80  1  16 adf
# b 660 root     root     28  96  1  16 adg
# b 660 root     root     28 112  1  16 adh
# b 660 root     root     28 128  1  16 adi
# b 660 root     root     28 144  1  16 adj
# b 660 root     root     28 160  1  16 adk
# b 660 root     root     28 176  1  16 adl
# b 660 root     root     28 192  1  16 adm
# b 660 root     root     28 208  1  16 adn
# b 660 root     root     28 224  1  16 ado
# b 660 root     root     28 240  1  16 adp

# Aaargh.  Change the 8 to a 1 on the next line for 2.4!
c 600 root     root     29   0 32   8 fb%d
b 660 root     disk     29   0  1   1 aztcd

#c 660 root     root     30   0  1   1 socksys
#c 660 root     root     30   1  1   1 spx
#c 660 root     root     30   2  1   1 inet/arp
#c 660 root     root     30   2  1   1 inet/icmp
#c 660 root     root     30   2  1   1 inet/ip
#c 660 root     root     30   2  1   1 inet/udp
#c 660 root     root     30   2  1   1 inet/tcp

b 660 root     root     30   0  1   1 cm205cd

c 600 root     sys      31   0  1   1 mpu401data
c 600 root     sys      31   1  1   1 mpu401stat
b 660 root     disk     31   0  1   8 rom%d
b 660 root     disk     31   8  1   8 rrom%d
b 660 root     disk     31  16  1   8 flash%d
b 660 root     disk     31  24  1   8 rflash%d

c 660 root     uucp     32   0  1  16 ttyX%d
b 660 root     disk     32   0  1   1 cm206cd

c 660 root     uucp     33   0  1  16 cux%d
b 660 root     disk     33   0  1  64 hde
b 660 root     disk     33  64  1  64 hdf

c 600 root     sys      34   0  1  16 scc%d
b 660 root     disk     34   0  1  64 hdg
b 660 root     disk     34  64  1  64 hdh

c 600 root     sys      35   0  1   4 midi%d
c 600 root     sys      35  64  1   4 rmidi%d
c 600 root     sys      35 128  1   4 smpte%d
b 600 root     root     35   0  1   1 slram

c 600 root     sys      36   0  1   1 route
c 600 root     sys      36   1  1   1 skip
c 660 root     root     36   2  1   1 fwmonitor
c 660 root     root     36  16  1  16 tap%d
b 660 root     root     36   0  1  64 eda
b 660 root     root     36  64  1  64 edb

c 660 root     disk     37   0  1 128 ht%d
c 660 root     disk     37 128  1 128 nht%d
b 660 root     root     37   0  1   1 z2ram

c 660 root     root     38   0  1  16 mlanai%d

c 660 root     root     39   0  1  16 ml16pa-a%d
c 660 root     root     39  16  1   1 ml16pa-d
c 660 root     root     39  17  1   3 ml16pa-c%d
c 660 root     root     39  32  1  16 ml16pb-a%d
c 660 root     root     39  48  1   1 ml16pb-d
c 660 root     root     39  49  1   3 ml16pb-c%d

c 660 root     sys      40   0  1   1 mmetfgrab
#b 660 root     root     40   0  1   1 eza

c 660 root     root     41   0  1   1 yamm
b 660 root     disk     41   0  1   1 bpcd

# Stay away from 42!

c 660 root     uucp     43   0  1  64 ttyI%d
b 660 root     disk     43   0  1 128 nb%d

c 660 root     uucp     44   0  1  64 cui%d
b 660 root     root     44   0  1  16 ftla
b 660 root     root     44  16  1  16 ftlb
b 660 root     root     44  32  1  16 ftlc
b 660 root     root     44  48  1  16 ftld
b 660 root     root     44  64  1  16 ftle
b 660 root     root     44  80  1  16 ftlf
b 660 root     root     44  96  1  16 ftlg
b 660 root     root     44 112  1  16 ftlh
b 660 root     root     44 128  1  16 ftli
b 660 root     root     44 144  1  16 ftlj
b 660 root     root     44 160  1  16 ftlk
b 660 root     root     44 176  1  16 ftll
b 660 root     root     44 192  1  16 ftlm
b 660 root     root     44 208  1  16 ftln
b 660 root     root     44 224  1  16 ftlo
b 660 root     root     44 240  1  16 ftlp

c 600 root     root     45   0  1  64 isdn%d
c 600 root     root     45  64  1  64 isdnctrl%d
c 600 root     root     45 128  1  64 ippp%d
c 600 root     root     45 255  1   1 isdninfo
b 660 root     disk     45   0  1  16 pda
b 660 root     disk     45  16  1  16 pdb
b 660 root     disk     45  32  1  16 pdc
b 660 root     disk     45  48  1  16 pdd

c 660 root     uucp     46   0  1  16 ttyR%d
b 660 root     disk     46   0  1   4 pcd%d

c 660 root     uucp     47   0  1  16 cur%d
b 660 root     disk     47   0  1   4 pf%d

c 660 root     uucp     48   0  1  16 ttyL%d
c 660 root     uucp     49   0  1  16 cul%d

c 660 root     root     51   0  1  16 bc%d

c 600 root     sys      52   0  1   4 dcbri%d

c 660 root     root     53   0  1   3 pd_bdm%d
c 660 root     root     53   3  1   3 icd_bdm%d

c 660 root     root     54   0  1   3 holter%d

c 660 root     root     55   0  1   1 dsp56k

c 660 root     root     56   0  1   1 adb
b 660 root     disk     56   0  1  64 hdi
b 660 root     disk     56  64  1  64 hdj

c 660 root     uucp     57   0  1  16 ttyP%d
b 660 root     disk     57   0  1  64 hdk
b 660 root     disk     57  64  1  64 hdl

c 660 root     uucp     58   0  1  16 cup%d

c 660 root     root     59   0  1   1 firewall
b 660 root     root     59   0  1   8 pda%d

# Here there be dragons.

c 600 root     sys      64   0  1   1 enskip

c 660 root     root     65   0  1   4 plink%d
c 660 root     root     65  64  1   4 rplink%d
c 660 root     root     65 128  1   4 plink%dd
c 660 root     root     65 192  1   4 rplink%dd
b 660 root     disk     65   0  1  16 sdq
b 660 root     disk     65  16  1  16 sdr
b 660 root     disk     65  32  1  16 sds
b 660 root     disk     65  48  1  16 sdt
b 660 root     disk     65  64  1  16 sdu
b 660 root     disk     65  80  1  16 sdv
b 660 root     disk     65  96  1  16 sdw
b 660 root     disk     65 112  1  16 sdx
b 660 root     disk     65 128  1  16 sdy
b 660 root     disk     65 144  1  16 sdz
b 660 root     disk     65 160  1  16 sdaa
b 660 root     disk     65 176  1  16 sdab
b 660 root     disk     65 192  1  16 sdac
b 660 root     disk     65 208  1  16 sdad
b 660 root     disk     65 224  1  16 sdae
b 660 root     disk     65 240  1  16 sdaf

c 660 root     root     66   0  1  16 yppcpci%d
b 660 root     disk     66   0  1  16 sdag
b 660 root     disk     66  16  1  16 sdah
b 660 root     disk     66  32  1  16 sdai
b 660 root     disk     66  48  1  16 sdaj
b 660 root     disk     66  64  1  16 sdak
b 660 root     disk     66  80  1  16 sdal
b 660 root     disk     66  96  1  16 sdam
b 660 root     disk     66 112  1  16 sdan
b 660 root     disk     66 128  1  16 sdao
b 660 root     disk     66 144  1  16 sdap
b 660 root     disk     66 160  1  16 sdaq
b 660 root     disk     66 176  1  16 sdar
b 660 root     disk     66 192  1  16 sdas
b 660 root     disk     66 208  1  16 sdat
b 660 root     disk     66 224  1  16 sdau
b 660 root     disk     66 240  1  16 sdav

c 600 root     sys      67   0  1   1 cfs0
b 660 root     disk     67   0  1  16 sdaw
b 660 root     disk     67  16  1  16 sdax
b 660 root     disk     67  32  1  16 sday
b 660 root     disk     67  48  1  16 sdaz
b 660 root     disk     67  64  1  16 sdba
b 660 root     disk     67  80  1  16 sdbb
b 660 root     disk     67  96  1  16 sdbc
b 660 root     disk     67 112  1  16 sdbd
b 660 root     disk     67 128  1  16 sdbe
b 660 root     disk     67 144  1  16 sdbf
b 660 root     disk     67 160  1  16 sdbg
b 660 root     disk     67 176  1  16 sdbh
b 660 root     disk     67 192  1  16 sdbi
b 660 root     disk     67 208  1  16 sdbj
b 660 root     disk     67 224  1  16 sdbk
b 660 root     disk     67 240  1  16 sdbl

c 600 root     sys      68   0  1   1 capi20
c 600 root     sys      68   1  1  20 capi20.%02d
b 660 root     disk     68   0  1  16 sdbm
b 660 root     disk     68  16  1  16 sdbn
b 660 root     disk     68  32  1  16 sdbo
b 660 root     disk     68  48  1  16 sdbp
b 660 root     disk     68  64  1  16 sdbq
b 660 root     disk     68  80  1  16 sdbr
b 660 root     disk     68  96  1  16 sdbs
b 660 root     disk     68 112  1  16 sdbt
b 660 root     disk     68 128  1  16 sdbu
b 660 root     disk     68 144  1  16 sdbv
b 660 root     disk     68 160  1  16 sdbw
b 660 root     disk     68 176  1  16 sdbx
b 660 root     disk     68 192  1  16 sdby
b 660 root     disk     68 208  1  16 sdbz
b 660 root     disk     68 224  1  16 sdca
b 660 root     disk     68 240  1  16 sdcb

c 660 root     root     69   0  1   1 ma16
b 660 root     disk     69   0  1  16 sdcc
b 660 root     disk     69  16  1  16 sdcd
b 660 root     disk     69  32  1  16 sdce
b 660 root     disk     69  48  1  16 sdcf
b 660 root     disk     69  64  1  16 sdcg
b 660 root     disk     69  80  1  16 sdch
b 660 root     disk     69  96  1  16 sdci
b 660 root     disk     69 112  1  16 sdcj
b 660 root     disk     69 128  1  16 sdck
b 660 root     disk     69 144  1  16 sdcl
b 660 root     disk     69 160  1  16 sdcm
b 660 root     disk     69 176  1  16 sdcn
b 660 root     disk     69 192  1  16 sdco
b 660 root     disk     69 208  1  16 sdcp
b 660 root     disk     69 224  1  16 sdcq
b 660 root     disk     69 240  1  16 sdcr

c 660 root     root     70   0  1   1 apscfg
c 660 root     root     70   1  1   1 apsauth
c 660 root     root     70   2  1   1 apslog
c 660 root     root     70   3  1   1 apsdbg
c 660 root     root     70  64  1   1 apsisdn
c 660 root     root     70  65  1   1 apsasync
c 660 root     root     70 128  1   1 apsmon
b 660 root     disk     70   0  1  16 sdcs
b 660 root     disk     70  16  1  16 sdct
b 660 root     disk     70  32  1  16 sdcu
b 660 root     disk     70  48  1  16 sdcv
b 660 root     disk     70  64  1  16 sdcw
b 660 root     disk     70  80  1  16 sdcx
b 660 root     disk     70  96  1  16 sdcy
b 660 root     disk     70 112  1  16 sdcz
b 660 root     disk     70 128  1  16 sdda
b 660 root     disk     70 144  1  16 sddb
b 660 root     disk     70 160  1  16 sddc
b 660 root     disk     70 176  1  16 sddd
b 660 root     disk     70 192  1  16 sdde
b 660 root     disk     70 208  1  16 sddf
b 660 root     disk     70 224  1  16 sddg
b 660 root     disk     70 240  1  16 sddh

c 660 root     uucp     71   0  1 256 ttyF%d
b 660 root     disk     71   0  1  16 sddi
b 660 root     disk     71  16  1  16 sddj
b 660 root     disk     71  32  1  16 sddk
b 660 root     disk     71  48  1  16 sddl
b 660 root     disk     71  64  1  16 sddm
b 660 root     disk     71  80  1  16 sddn
b 660 root     disk     71  96  1  16 sddo
b 660 root     disk     71 112  1  16 sddp
b 660 root     disk     71 128  1  16 sddq
b 660 root     disk     71 144  1  16 sddr
b 660 root     disk     71 160  1  16 sdds
b 660 root     disk     71 176  1  16 sddt
b 660 root     disk     71 192  1  16 sddu
b 660 root     disk     71 208  1  16 sddv
b 660 root     disk     71 224  1  16 sddw
b 660 root     disk     71 240  1  16 sddx

c 660 root     uucp     72   0  1 256 cuf%d

c 600 root     sys      73   0  4   4 ip2ipl%d
c 600 root     sys      73   1  4   4 ip2stat%d

c 660 root     root     74   0  1  16 SCI/%d

c 660 root     uucp     75   0  1  16 ttyW%d
c 660 root     uucp     76   0  1  16 cuw%d

c 600 root     sys      77   0  1   1 qng

#c 660 root     uucp     78   0  1  16 ttyM%x
#c 660 root     uucp     79   0  1  16 cum%d

c 660 root     root     80   0  1   1 at200
b 660 root     root     80   0  1  16 i2o/hda
b 660 root     root     80  16  1  16 i2o/hdb
b 660 root     root     80  32  1  16 i2o/hdc
b 660 root     root     80  48  1  16 i2o/hdd
b 660 root     root     80  64  1  16 i2o/hde
b 660 root     root     80  80  1  16 i2o/hdf
b 660 root     root     80  96  1  16 i2o/hdg
b 660 root     root     80 112  1  16 i2o/hdh
b 660 root     root     80 128  1  16 i2o/hdi
b 660 root     root     80 144  1  16 i2o/hdj
b 660 root     root     80 160  1  16 i2o/hdk
b 660 root     root     80 176  1  16 i2o/hdl
b 660 root     root     80 192  1  16 i2o/hdm
b 660 root     root     80 208  1  16 i2o/hdn
b 660 root     root     80 224  1  16 i2o/hdo
b 660 root     root     80 240  1  16 i2o/hdp

c 600 root     sys      81   0  1  64 video%d
c 600 root     sys      81  64  1  64 radio%d
c 600 root     sys      81 192  1  32 vtx%d
c 600 root     sys      81 224  1  32 vbi%d

b 660 root     root     81   0  1  16 i2o/hdq
b 660 root     root     81  16  1  16 i2o/hdr
b 660 root     root     81  32  1  16 i2o/hds
b 660 root     root     81  48  1  16 i2o/hdt
b 660 root     root     81  64  1  16 i2o/hdu
b 660 root     root     81  80  1  16 i2o/hdv
b 660 root     root     81  96  1  16 i2o/hdw
b 660 root     root     81 112  1  16 i2o/hdx
b 660 root     root     81 128  1  16 i2o/hdy
b 660 root     root     81 144  1  16 i2o/hdz
b 660 root     root     81 160  1  16 i2o/hdaa
b 660 root     root     81 176  1  16 i2o/hdab
b 660 root     root     81 192  1  16 i2o/hdac
b 660 root     root     81 208  1  16 i2o/hdad
b 660 root     root     81 224  1  16 i2o/hdae
b 660 root     root     81 240  1  16 i2o/hdaf

c 600 root     sys      82   0  1   4 winradio%d

b 660 root     root     82   0  1  16 i2o/hdag
b 660 root     root     82  16  1  16 i2o/hdah
b 660 root     root     82  32  1  16 i2o/hdai
b 660 root     root     82  48  1  16 i2o/hdaj
b 660 root     root     82  64  1  16 i2o/hdak
b 660 root     root     82  80  1  16 i2o/hdal
b 660 root     root     82  96  1  16 i2o/hdam
b 660 root     root     82 112  1  16 i2o/hdan
b 660 root     root     82 128  1  16 i2o/hdao
b 660 root     root     82 144  1  16 i2o/hdap
b 660 root     root     82 160  1  16 i2o/hdaq
b 660 root     root     82 176  1  16 i2o/hdar
b 660 root     root     82 192  1  16 i2o/hdas
b 660 root     root     82 208  1  16 i2o/hdat
b 660 root     root     82 224  1  16 i2o/hdau
b 660 root     root     82 240  1  16 i2o/hdav

c 600 root     sys      83   0  1   1 vtx
c 600 root     sys      83  16  1   1 vttuner

b 660 root     root     83   0  1  16 i2o/hdaw
b 660 root     root     83  16  1  16 i2o/hdax
b 660 root     root     83  32  1  16 i2o/hday
b 660 root     root     83  48  1  16 i2o/hdaz
b 660 root     root     83  64  1  16 i2o/hdba
b 660 root     root     83  80  1  16 i2o/hdbb
b 660 root     root     83  96  1  16 i2o/hdbc
b 660 root     root     83 112  1  16 i2o/hdbd
b 660 root     root     83 128  1  16 i2o/hdbe
b 660 root     root     83 144  1  16 i2o/hdbf
b 660 root     root     83 160  1  16 i2o/hdbg
b 660 root     root     83 176  1  16 i2o/hdbh
b 660 root     root     83 192  1  16 i2o/hdbi
b 660 root     root     83 208  1  16 i2o/hdbj
b 660 root     root     83 224  1  16 i2o/hdbk
b 660 root     root     83 240  1  16 i2o/hdbl

c 660 root     root     84   0  1   2 ihcp%d

b 660 root     root     84   0  1  16 i2o/hdbm
b 660 root     root     84  16  1  16 i2o/hdbn
b 660 root     root     84  32  1  16 i2o/hdbo
b 660 root     root     84  48  1  16 i2o/hdbp
b 660 root     root     84  64  1  16 i2o/hdbq
b 660 root     root     84  80  1  16 i2o/hdbr
b 660 root     root     84  96  1  16 i2o/hdbs
b 660 root     root     84 112  1  16 i2o/hdbt
b 660 root     root     84 128  1  16 i2o/hdbu
b 660 root     root     84 144  1  16 i2o/hdbv
b 660 root     root     84 160  1  16 i2o/hdbw
b 660 root     root     84 176  1  16 i2o/hdbx
b 660 root     root     84 192  1  16 i2o/hdby
b 660 root     root     84 208  1  16 i2o/hdbz
b 660 root     root     84 224  1  16 i2o/hdca
b 660 root     root     84 240  1  16 i2o/hdcb

c 660 root     root     85   0  1   1 shmiq
c 660 root     root     85   1  1   8 qcntl%d

b 660 root     root     85   0  1  16 i2o/hdcc
b 660 root     root     85  16  1  16 i2o/hdcd
b 660 root     root     85  32  1  16 i2o/hdce
b 660 root     root     85  48  1  16 i2o/hdcf
b 660 root     root     85  64  1  16 i2o/hdcg
b 660 root     root     85  80  1  16 i2o/hdch
b 660 root     root     85  96  1  16 i2o/hdci
b 660 root     root     85 112  1  16 i2o/hdcj
b 660 root     root     85 128  1  16 i2o/hdck
b 660 root     root     85 144  1  16 i2o/hdcl
b 660 root     root     85 160  1  16 i2o/hdcm
b 660 root     root     85 176  1  16 i2o/hdcn
b 660 root     root     85 192  1  16 i2o/hdco
b 660 root     root     85 208  1  16 i2o/hdcp
b 660 root     root     85 224  1  16 i2o/hdcq
b 660 root     root     85 240  1  16 i2o/hdcr

c 660 root     root     86   0  1   8 sch%d

b 660 root     root     86   0  1  16 i2o/hdcs
b 660 root     root     86  16  1  16 i2o/hdct
b 660 root     root     86  32  1  16 i2o/hdcu
b 660 root     root     86  48  1  16 i2o/hdcv
b 660 root     root     86  64  1  16 i2o/hdcw
b 660 root     root     86  80  1  16 i2o/hdcx
b 660 root     root     86  96  1  16 i2o/hdcy
b 660 root     root     86 112  1  16 i2o/hdcz
b 660 root     root     86 128  1  16 i2o/hdda
b 660 root     root     86 144  1  16 i2o/hddb
b 660 root     root     86 160  1  16 i2o/hddc
b 660 root     root     86 176  1  16 i2o/hddd
b 660 root     root     86 192  1  16 i2o/hdde
b 660 root     root     86 208  1  16 i2o/hddf
b 660 root     root     86 224  1  16 i2o/hddg
b 660 root     root     86 240  1  16 i2o/hddh

c 660 root     root     87   0  1   8 controla%d

b 660 root     root     87   0  1  16 i2o/hddi
b 660 root     root     87  16  1  16 i2o/hddj
b 660 root     root     87  32  1  16 i2o/hddk
b 660 root     root     87  48  1  16 i2o/hddl
b 660 root     root     87  64  1  16 i2o/hddm
b 660 root     root     87  80  1  16 i2o/hddn
b 660 root     root     87  96  1  16 i2o/hddo
b 660 root     root     87 112  1  16 i2o/hddp
b 660 root     root     87 128  1  16 i2o/hddq
b 660 root     root     87 144  1  16 i2o/hddr
b 660 root     root     87 160  1  16 i2o/hdds
b 660 root     root     87 176  1  16 i2o/hddt
b 660 root     root     87 192  1  16 i2o/hddu
b 660 root     root     87 208  1  16 i2o/hddv
b 660 root     root     87 224  1  16 i2o/hddw
b 660 root     root     87 240  1  16 i2o/hddx

c 600 root     sys      88   0  1   8 comx%d

b 660 root     root     88   0  1  64 hdm
b 660 root     root     88  64  1  64 hdn

c 600 root     sys      89   0  1   8 i2c-%d

b 660 root     root     89   0  1  64 hdo
b 660 root     root     89  64  1  64 hdp

c 660 root     root     90   0  2  16 mtd%d
c 660 root     root     90   1  2  16 mtdr%d

b 660 root     root     90   0  1  64 hdq
b 660 root     root     90  64  1  64 hdr

c 660 root     root     91   0  1  16 can%d

b 660 root     root     91   0  1  64 hds
b 660 root     root     91  64  1  64 hdt

b 660 root     root     92   0  1  64 ppdd%d

c 660 root     sys      93   0  1   8 iscc%d
c 660 root     sys      93 128  1   8 isccctl%d

b 660 root     root     93   0 16   1 nftla
b 660 root     root     93  16 16  15 nftl%c a

c 660 root     sys      94   0  1   8 dcxx%d

c 600 root     sys      95   0  1   1 ipl
c 600 root     sys      95   1  1   1 ipnat
c 600 root     sys      95   2  1   1 ipstate
c 600 root     sys      95   3  1   1 ipauth

c 660 root     disk     96   0  1  16 pt%d
c 660 root     disk     96 128  1  16 npt%d

b 660 root     root     96   0  8   4 msd%d

c 600 root     sys      97   0  1   4 pg%d
c 660 root     root     98   0  1   4 comedi%d
c 660 root     daemon   99   0  1   8 parport%d
c 660 root     root    100   0  1   8 phone%d

c 660 root     root    101   0  1   1 mdspstat
c 660 root     root    101   1  1  16 mdsp%d 1

c 600 root     sys     102   0  1   4 tlk%d

c 600 root     sys     103   0  1   1 xfs0

c 660 root     uucp    105   0  1  16 ttyV%d
c 660 root     uucp    106   0  1  16 cuv%d

c 660 root     root    107   0  1   1 3dfx
c 660 root     root    108   0  1   1 ppp

c 600 root     sys     110   0  1   8 srnd%d
c 660 root     root    111   0  1   8 av%d

c 660 root     uucp    112   0  1  16 ttyM%x
c 660 root     uucp    113   0  1  16 cum%d

c 660 root     root    114   0  1  16 ise%d
c 660 root     root    114 128  1  16 isex%d

c 660 root     root    115   0  1   1 speaker

c 660 root     root    117   0  1  16 cosa0c%d
c 660 root     root    117  16  1  16 cosa1c%d

c 660 root     root    118   0  1  16 solnp%d
c 660 root     root    118 128  1  16 solnpctl%d

c 660 root     root    119   0  1  16 vnet%d

c 660 root     root    144   0  1  64 pppox%d

c 600 root     sys     145   0 64   4 sam%d_mixer
c 600 root     sys     145   1 64   4 sam%d_sequencer
c 600 root     sys     145   2 64   4 sam%d_midi00
c 600 root     sys     145   3 64   4 sam%d_dsp
c 600 root     sys     145   4 64   4 sam%d_audio
c 600 root     sys     145   6 64   4 sam%d_sndstat
c 600 root     sys     145  18 64   4 sam%d_midi01
c 600 root     sys     145  34 64   4 sam%d_midi02
c 600 root     sys     145  50 64   4 sam%d_midi03

c 660 root     root    146   0  1   8 scramnet%d
c 660 root     root    147   0  1   8 aureal%d

c 660 root     uucp    148   0  1  16 ttyT%d
c 660 root     uucp    149   0  1  16 cut%d

c 660 root     root    150   0  1  16 rtf%d

c 660 root     root    151   0  1  16 dpti%d

c 660 root     uucp    154   0  1 256 ttySR%d
c 660 root     uucp    155   0  1 256 cusr%d
c 660 root     uucp    156   0  1 256 ttySR%d 256
c 660 root     uucp    157   0  1 256 cusr%d  256

c 660 root     root    158   0  1  16 gfax%d
c 660 root     root    159   0  1  16 ixj%d
c 660 root     root    160   0  1  16 gpib%d

c 660 root     root    161   0  1  16 ircomm%d
c 660 root     root    161  16  1  16 irlpt%d

# c 660 root     disk    162   1  1 256 raw%d

c 660 root     root    163   0  1  64 bimrt%d

c 660 root     uucp    164   0  1  64 ttyCH%d
c 660 root     uucp    165   0  1  64 cuch%d

# c 660 root     root    166   0  1  16 ttyACM%d
# c 660 root     uucp    167   0  1  16 cuacm%d

c 660 root     root    168   0  1  64 ecsa%d
c 660 root     root    169   0  1  64 ecsa8-%d

c 660 root     root    170   0  1  64 megarac%d

c 660 root     uucp    171   0  1 128 ttyMX%d
c 660 root     root    171 128  1   1 moxactl
c 660 root     uucp    172   0  1 128 cumx%d

c 660 root     uucp    174   0  1  16 ttySI%d
c 660 root     uucp    175   0  1  16 cusi%d

c 660 root     root    176   0  1  16 nfastpci%d

c 660 root     root    177   0  1  16 pcilynx/aux%d
c 660 root     root    177  16  1  16 pcilynx/rom%d
c 660 root     root    177  32  1  16 pcilynx/ram%d

c 660 root     root    178   0  1  16 clanvi%d

c 660 root     root    179   0  1  16 dvxirq%d

# c 660 root     daemon  180   0  1  16 usb/lp%d
# c 666 root     sys     180  16  1  16 usb/mouse%d
# c 660 root     root    180  32  1  16 usb/ez%d
# c 660 root     root    180  48  1  16 usb/scanner%d

c 660 root     root    181   0  1  16 pcfclock%d
c 660 root     root    182   0  1  16 pethr%d

c 660 root     root    183   0  1  16 ss5136dn%d
c 660 root     root    184   0  1  16 pevss%d
c 660 root     root    186   0  1  16 obd%d

c 660 root     uucp    188   0  1  16 ttyUSB%d
c 660 root     uucp    189   0  1  16 cuusb%d

c 660 root     root    190   0  1  16 kctt%d
