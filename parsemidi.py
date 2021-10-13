#!/usr/bin/python3
# parsemidi.py 
import sys, os
f = open(sys.argv[1], 'rb')
midi = f.read() 
f.close()

i = 0

if midi[0:4] != b'MThd':
    print('bad midi file!')
    os.quit()

i = 4
header_len = midi[i] << 24 | midi[i+1] << 16 | midi[i+2] << 8 | midi[i+3]
i += 4

header = midi[i:i+header_len]
if header[1] == 1:
    print('format 1')
else:
    print('not format 1. exiting')
    os.exit() 

numtracks = header[3] 
print('tracks: ', numtracks)

ticks_per_note = header[4] << 8 | header[5] 
print('ticks per quarter', ticks_per_note)

i += header_len

#$8n - note off
#$9n - note on
#$An - pf key pressure
#$Bn - control change (special)
#$Cn - change patch
#$Dn - channel pressure
#$En - pitch wheel
# n = midi channel

need_time_delta = True
run_status = None

while i < 200:#len(midi):
    if midi[i:i+4] == b'MTrk':
        tlen = midi[i+4:i+8]
        slen = tlen[0] << 24 | tlen[1] << 16 | tlen[2] << 8 | tlen[3]
        print('new track, length: ', slen)
        need_time_delta = True
        i += 7
    elif midi[i:i+2] == b'\xff\x58': # time sig
        num = midi[i+3]
        den = 2**midi[i+4]
        c_per_tick = midi[i+5]
        per_qtr = midi[i+6]
        print('time sig: ',num,den)
        print('clocks per tick:', c_per_tick)
        print('32nd notes per midi 4th:,', per_qtr)
        need_time_delta = True
        i += 6
    elif midi[i:i+2] == b'\xff\x51':
        tempo = midi[i+3:i+6]
        tempo = tempo[0] << 16 | tempo[1] << 8 | tempo[2]
        print('tempo (ms/qtr):',tempo) 
        bpm = (600000/tempo) * 100
        print('bpm', bpm)
        need_time_delta = True
        i += 5
    elif midi[i:i+2] == b'\xff\x03':
        strlen = midi[i+2]
        txt = ''
        while strlen > 0:
            txt += chr(midi[i+3])
            i += 1
            strlen -= 1
        print(txt)
        need_time_delta = True
        i += 2
    elif midi[i:i+3] == b'\xff\x2f\x00':
        print('end of track')
        i += 2
    else:
        if(need_time_delta):
            # get variable len
            d = []
            while(midi[i] & 0x80):
                d.append(midi[i] & 0x7f)
                i += 1
            d.append(midi[i])
            f = 0
            df = 0
            while f < len(d):
                df += d[f] << ((len(d)-f) * 4)
                f += 1
            if(df > 0):
                print('vlq: ',df)
            need_time_delta = False
        else:
            if(run_status):
                if(midi[i] > 0x7f):
                    run_status = 0
                else:
                    i -= 1
            if ((midi[i] & 0xf0) == 0x80) or (run_status == 0x80):
                ke = midi[i+1]
                ve = midi[i+2]
                print('note off ch',midi[i] & 0xf, 'key',ke, 'vel',ve)
                run_status = 0x80
                i += 2
            elif ((midi[i] & 0xf0) == 0xb0) or (run_status == 0xb0):
                print('ch', midi[i] & 0xf, 'sp. control', hex(midi[i+1]), hex(midi[i+2]))
                run_status = 0xb0
                i += 2
            elif ((midi[i] & 0xf0) == 0xc0) or (run_status == 0xc0):
                print('set ch', midi[i] & 0xf, 'to instrument', midi[i+1])
                run_status = 0xc0
                i += 1
            elif ((midi[i] & 0xf0) == 0x90) or (run_status == 0x90):
                ke = midi[i+1]
                ve = midi[i+2]
                print('play note ch',midi[i] & 0xf, 'key',ke, 'vel',ve)
                run_status = 0x90
                i += 2
            #elif (midi[i] == 7):
            #    print('channel vol')
            need_time_delta = True
    
    i += 1

# y = 60000/x