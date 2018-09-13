RMC000:                             //RMC000:
a = IO[BC]          ;f=a&0xff;E = a                 ;F.Z=((a&0xff)==0)  ;              ;                             //      !IN      E,(C)
a = C + 1           ;f=a&0xff;C = a                 ;F.Z=((a&0xff)==0)  ;              ;                             //      INC     C
a = IO[BC]          ;f=a&0xff;D = a                 ;F.Z=((a&0xff)==0)  ;              ;                             //      !IN      D,(C)
a = B + 1           ;f=a&0xff;B = a                 ;F.Z=((a&0xff)==0)  ;              ;                             //      INC     B
a = IO[BC]          ;f=a&0xff;H = a                 ;F.Z=((a&0xff)==0)  ;              ;                             //      !IN      H,(C)
a = C - 1           ;f=a&0xff;C = a                 ;F.Z=((a&0xff)==0)  ;              ;                             //      DEC     C
a = IO[BC]          ;f=a&0xff;L = a                 ;F.Z=((a&0xff)==0)  ;              ;                             //      !IN      L,(C)
a = B - 1           ;f=a&0xff;B = a                 ;F.Z=((a&0xff)==0)  ;              ;                             //      DEC     B
                    ;        ;RET(goto **(--sp);)         ;                                  ;                             //      RET
RMC00D:                             //RMC00D:
                    ;        ;B = MEM[IX+0x01]      ;                                  ;                             //      LD      B,(IX+01h)
                    ;        ;C = MEM[IX+0x00]      ;                                  ;                             //      LD      C,(IX+00h)
                    ;        ;A = MEM[IX+0x04]      ;                                  ;                             //      LD      A,(IX+04h)
a = A - 0x02        ;f=a     ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;                             //      CP      02h
                    ;        ;if (  F.C ) {goto RMC023;}else{}               ;                                   //      JR      C,RMC023
                    ;        ;GOS(*(sp++) = (int)&&C01A;goto RMC000;C01A:a=a;)               ;                             //      CALL    RMC000
                    ;        ;A = 0x30              ;                                  ;                             //      LD      A,30h
a = A - D           ;f=a     ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;                             //      CP      D
                    ;        ;if (  F.C ) {RET(goto **(--sp););}else{}          ;                                    //      RET     C
a = A - E           ;f=a     ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;                             //      CP      E
                    ;        ;if (  F.C ) {RET(goto **(--sp););}else{}          ;                                    //      RET     C
RMC023:                             //RMC023:
                    ;        ;A = 0x00              ;                                  ;                             //      LD      A,00h
                    ;        ;IO[BC] = A            ;                                  ;                             //      !OUT     (C),A
a = C + 1           ;f=a&0xff;C = a                 ;F.Z=((a&0xff)==0)  ;              ;                             //      INC     C
                    ;        ;IO[BC] = A            ;                                  ;                             //      !OUT     (C),A
a = B + 1           ;f=a&0xff;B = a                 ;F.Z=((a&0xff)==0)  ;              ;                             //      INC     B
                    ;        ;IO[BC] = A            ;                                  ;                             //      !OUT     (C),A
a = C - 1           ;f=a&0xff;C = a                 ;F.Z=((a&0xff)==0)  ;              ;                             //      DEC     C
                    ;        ;IO[BC] = A            ;                                  ;                             //      !OUT     (C),A
                    ;        ;GOS(*(sp++) = (int)&&C030;goto RMC000;C030:a=a;)               ;                             //      CALL    RMC000
                    ;        ;A = 0x30              ;                                  ;                             //      LD      A,30h
a = A - H           ;f=a     ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;                             //      CP      H
        ;if ( !F.C ) goto RMC0C2   ;                                  ;                                   //      JP      NC,RMC0C2
a = A - L           ;f=a     ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;                             //      CP      L
        ;if ( !F.C ) goto RMC0C2   ;                                  ;                                   //      JP      NC,RMC0C2
                    ;        ;A = 0x02              ;                                  ;                             //      LD      A,02h
a = A - MEM[IX+0x04];f=a     ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;                             //      CP      (IX+04h)
                    ;        ;if ( !F.C ) {goto RMC04F;}else{}               ;                                   //      JR      NC,RMC04F
a = MEM[IX+0x04] - 1;f=a&0xff;MEM[IX+0x04] = a      ;F.Z=((a&0xff)==0)  ;              ;                             //      DEC     (IX+04h)
                    ;        ;A = 0x01              ;                                  ;                             //      LD      A,01h
a = A - MEM[IX+0x04];f=a     ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;                             //      CP      (IX+04h)
        ;if (  F.C ) goto RMC0F0   ;                                  ;                                   //      JP      C,RMC0F0
RMC04F:                             //RMC04F:
                    ;        ;A = MEM[IX+0x03]      ;                                  ;                             //      LD      A,(IX+03h)
a = A + 0x80        ;f=a&0xff;A = a                 ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;                             //      ADD     80h
a = A - 0x85        ;f=a     ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;                             //      CP      85h
        ;if ( !F.C ) goto RMC0EB   ;                                  ;                                   //      JP      NC,RMC0EB
                    ;        ;A = MEM[IX+0x06]      ;                                  ;                             //      LD      A,(IX+06h)
a = A & (1<<0)     ;f=a&0xff;                      ;F.Z=((a&0xff)==0)  ;              ;                             //      BIT     0,A
                    ;        ;if (  F.Z ) {goto RMC095;}else{}               ;                                   //      JR      Z,RMC095
a = A & (1<<1)     ;f=a&0xff;                      ;F.Z=((a&0xff)==0)  ;              ;                             //      BIT     1,A
        ;if (  F.Z ) goto RMC0F0   ;                                  ;                                   //      JP      Z,RMC0F0
                    ;        ;D = A                 ;                                  ;                             //      LD      D,A
                    ;        ;A = MEM[IX+0x04]      ;                                  ;                             //      LD      A,(IX+04h)
a = A - 0x02        ;f=a     ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;                             //      CP      02h
                    ;        ;if ( !F.C ) {goto RMC07E;}else{}               ;                                   //      JR      NC,RMC07E
                    ;        ;MEM[IX+0x03] = 0x00   ;                                  ;                             //      LD      (IX+03h),00h
                    ;        ;A = D                 ;                                  ;                             //      LD      A,D
a = A & (1<<2)     ;f=a&0xff;                      ;F.Z=((a&0xff)==0)  ;              ;                             //      BIT     2,A
                    ;        ;if (  F.Z ) {goto RMC085;}else{}               ;                                   //      JR      Z,RMC085
a = A & (1<<3)     ;f=a&0xff;                      ;F.Z=((a&0xff)==0)  ;              ;                             //      BIT     3,A
                    ;        ;if (  F.Z ) {goto RMC08B;}else{}               ;                                   //      JR      Z,RMC08B
                    ;        ;MEM[IX+0x02] = 0x00   ;                                  ;                             //      LD      (IX+02h),00h
RMC07E:                             //RMC07E:
                    ;        ;MEM[IX+0x04] = 0x00   ;                                  ;                             //      LD      (IX+04h),00h
                    ;        ;goto RMC10D               ;                                  ;                             //      JP      RMC10D
RMC085:                             //RMC085:
                    ;        ;MEM[IX+0x02] = 0xFE   ;                                  ;                             //      LD      (IX+02h),FEh
                    ;        ;goto RMC08F               ;                                  ;                             //      JR      RMC08F
RMC08B:                             //RMC08B:
                    ;        ;MEM[IX+0x02] = 0x02   ;                                  ;                             //      LD      (IX+02h),02h
RMC08F:                             //RMC08F:
                    ;        ;MEM[IX+0x04] = 0x01   ;                                  ;                             //      LD      (IX+04h),01h
                    ;        ;goto RMC10D               ;                                  ;                             //      JR      RMC10D
RMC095:                             //RMC095:
                    ;        ;D = A                 ;                                  ;                             //      LD      D,A
                    ;        ;A = MEM[IX+0x04]      ;                                  ;                             //      LD      A,(IX+04h)
a = A - 0x02        ;f=a     ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;                             //      CP      02h
                    ;        ;A = D                 ;                                  ;                             //      LD      A,D
                    ;        ;if ( !F.C ) {goto RMC0BC;}else{}               ;                                   //      JR      NC,RMC0BC
                    ;        ;MEM[IX+0x03] = 0xFF   ;                                  ;                             //      LD      (IX+03h),FFh
RMC0A2:                             //RMC0A2:
a = A & (1<<2)     ;f=a&0xff;                      ;F.Z=((a&0xff)==0)  ;              ;                             //      BIT     2,A
                    ;        ;if (  F.Z ) {goto RMC0B0;}else{}               ;                                   //      JR      Z,RMC0B0
a = A & (1<<3)     ;f=a&0xff;                      ;F.Z=((a&0xff)==0)  ;              ;                             //      BIT     3,A
                    ;        ;if (  F.Z ) {goto RMC0B6;}else{}               ;                                   //      JR      Z,RMC0B6
                    ;        ;MEM[IX+0x02] = 0x00   ;                                  ;                             //      LD      (IX+02h),00h
                    ;        ;goto RMC07E               ;                                  ;                             //      JR      RMC07E
RMC0B0:                             //RMC0B0:
                    ;        ;MEM[IX+0x02] = 0xFF   ;                                  ;                             //      LD      (IX+02h),FFh
                    ;        ;goto RMC07E               ;                                  ;                             //      JR      RMC07E
RMC0B6:                             //RMC0B6:
                    ;        ;MEM[IX+0x02] = 0x01   ;                                  ;                             //      LD      (IX+02h),01h
                    ;        ;goto RMC07E               ;                                  ;                             //      JR      RMC07E
RMC0BC:                             //RMC0BC:
                    ;        ;MEM[IX+0x03] = 0xFB   ;                                  ;                             //      LD      (IX+03h),FBh
                    ;        ;goto RMC0A2               ;                                  ;                             //      JR      RMC0A2
RMC0C2:                             //RMC0C2:
                    ;        ;A = MEM[IX+0x06]      ;                                  ;                             //      LD      A,(IX+06h)
a = A & (1<<0)     ;f=a&0xff;                      ;F.Z=((a&0xff)==0)  ;              ;                             //      BIT     0,A
                    ;        ;if (  F.Z ) {goto RMC0CE;}else{}               ;                                   //      JR      Z,RMC0CE
a = MEM[IX+0x03] + 1;f=a&0xff;MEM[IX+0x03] = a      ;F.Z=((a&0xff)==0)  ;              ;                             //      INC     (IX+03h)
                    ;        ;goto RMC07E               ;                                  ;                             //      JR      RMC07E
RMC0CE:                             //RMC0CE:
a = MEM[IX+0x03] - 1;f=a&0xff;MEM[IX+0x03] = a      ;F.Z=((a&0xff)==0)  ;              ;                             //      DEC     (IX+03h)
a = A & (1<<2)     ;f=a&0xff;                      ;F.Z=((a&0xff)==0)  ;              ;                             //      BIT     2,A
                    ;        ;if (  F.Z ) {goto RMC0DD;}else{}               ;                                   //      JR      Z,RMC0DD
a = A & (1<<3)     ;f=a&0xff;                      ;F.Z=((a&0xff)==0)  ;              ;                             //      BIT     3,A
                    ;        ;if (  F.Z ) {goto RMC0E1;}else{}               ;                                   //      JR      Z,RMC0E1
                    ;        ;A = 0x00              ;                                  ;                             //      LD      A,00h
                    ;        ;goto RMC0E3               ;                                  ;                             //      JR      RMC0E3
RMC0DD:                             //RMC0DD:
                    ;        ;A = 0xFF              ;                                  ;                             //      LD      A,FFh
                    ;        ;goto RMC0E3               ;                                  ;                             //      JR      RMC0E3
RMC0E1:                             //RMC0E1:
                    ;        ;A = 0x01              ;                                  ;                             //      LD      A,01h
RMC0E3:                             //RMC0E3:
a = A + MEM[IX+0x02];f=a&0xff;A = a                 ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;                             //      ADD     (IX+02h)
                    ;        ;MEM[IX+0x02] = A      ;                                  ;                             //      LD      (IX+02h),A
                    ;        ;goto RMC07E               ;                                  ;                             //      JR      RMC07E
RMC0EB:                             //RMC0EB:
a = A - 0x82        ;f=a     ;A = a                 ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;                             //      SUB     82h
                    ;        ;MEM[IX+0x04] = A      ;                                  ;                             //      LD      (IX+04h),A
RMC0F0:                             //RMC0F0:
                    ;        ;A = 0x00              ;                                  ;                             //      LD      A,00h
                    ;        ;MEM[IX+0x02] = A      ;                                  ;                             //      LD      (IX+02h),A
                    ;        ;MEM[IX+0x03] = A      ;                                  ;                             //      LD      (IX+03h),A
                    ;        ;A = MEM[IX+0x07]      ;                                  ;                             //      LD      A,(IX+07h)
a = A & 0xF0        ;f=a&0xff;A = a                 ;F.Z=((a&0xff)==0)  ;F.C=0         ;                             //      AND     F0h
a = A | 0x01        ;f=a&0xff;A = a                 ;F.Z=((a&0xff)==0)  ;F.C=0         ;                             //      OR      01h
                    ;        ;MEM[IX+0x07] = A      ;                                  ;                             //      LD      (IX+07h),A
                    ;        ;A = 0x01              ;                                  ;                             //      LD      A,01h
a = A - MEM[IX+0x04];f=a     ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;                             //      CP      (IX+04h)
                    ;        ;if (  F.C ) {goto RMC10D;}else{}               ;                                   //      JR      C,RMC10D
                    ;        ;MEM[IX+0x04] = 0x02   ;                                  ;                             //      LD      (IX+04h),02h
RMC10D:                             //RMC10D:
                    ;        ;A = MEM[IX+0x02]      ;                                  ;                             //      LD      A,(IX+02h)
a = A + 0x80        ;f=a&0xff;A = a                 ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;                             //      ADD     80h
a = A - 0x83        ;f=a     ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;                             //      CP      83h
                    ;        ;if (  F.C ) {goto RMC11A;}else{}               ;                                   //      JR      C,RMC11A
                    ;        ;MEM[IX+0x02] = 0x02   ;                                  ;                             //      LD      (IX+02h),02h
RMC11A:                             //RMC11A:
a = A - 0x7E        ;f=a     ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;                             //      CP      7Eh
                    ;        ;if ( !F.C ) {goto RMC122;}else{}               ;                                   //      JR      NC,RMC122
                    ;        ;MEM[IX+0x02] = 0xFE   ;                                  ;                             //      LD      (IX+02h),FEh
RMC122:                             //RMC122:
                    ;        ;A = MEM[IX+0x03]      ;                                  ;                             //      LD      A,(IX+03h)
a = A + 0x80        ;f=a&0xff;A = a                 ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;                             //      ADD     80h
a = A - 0x89        ;f=a     ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;                             //      CP      89h
                    ;        ;if (  F.C ) {goto RMC12F;}else{}               ;                                   //      JR      C,RMC12F
                    ;        ;MEM[IX+0x03] = 0x08   ;                                  ;                             //      LD      (IX+03h),08h
RMC12F:                             //RMC12F:
a = A - 0x78        ;f=a     ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;                             //      CP      78h
                    ;        ;if ( !F.C ) {goto RMC137;}else{}               ;                                   //      JR      NC,RMC137
                    ;        ;MEM[IX+0x03] = 0xF8   ;                                  ;                             //      LD      (IX+03h),F8h
RMC137:                             //RMC137:
                    ;        ;B = MEM[IX+0x01]      ;                                  ;                             //      LD      B,(IX+01h)
                    ;        ;C = MEM[IX+0x00]      ;                                  ;                             //      LD      C,(IX+00h)
                    ;        ;A = MEM[IX+0x02]      ;                                  ;                             //      LD      A,(IX+02h)
a = A - 0xFE        ;f=a     ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;                             //      CP      FEh
                    ;        ;if ( !F.C ) {goto RMC14A;}else{}               ;                                   //      JR      NC,RMC14A
a = A - 0x00        ;f=a     ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;                             //      CP      00h
                    ;        ;if (  F.Z ) {goto RMC14B;}else{}               ;                                   //      JR      Z,RMC14B
a = C + 1           ;f=a&0xff;C = a                 ;F.Z=((a&0xff)==0)  ;              ;                             //      INC     C
a = C + 1           ;f=a&0xff;C = a                 ;F.Z=((a&0xff)==0)  ;              ;                             //      INC     C
RMC14A:                             //RMC14A:
a = C - 1           ;f=a&0xff;C = a                 ;F.Z=((a&0xff)==0)  ;              ;                             //      DEC     C
RMC14B:                             //RMC14B:
                    ;        ;A = MEM[IX+0x03]      ;                                  ;                             //      LD      A,(IX+03h)
a = A - 0xFC        ;f=a     ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;                             //      CP      FCh
                    ;        ;if ( !F.C ) {goto RMC163;}else{}               ;                                   //      JR      NC,RMC163
a = A - 0xF8        ;f=a     ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;                             //      CP      F8h
                    ;        ;if ( !F.C ) {goto RMC162;}else{}               ;                                   //      JR      NC,RMC162
a = A - 0x00        ;f=a     ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;                             //      CP      00h
                    ;        ;if (  F.Z ) {goto RMC164;}else{}               ;                                   //      JR      Z,RMC164
a = A - 0x04        ;f=a     ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;                             //      CP      04h
                    ;        ;if (  F.C ) {goto RMC15F;}else{}               ;                                   //      JR      C,RMC15F
a = B + 1           ;f=a&0xff;B = a                 ;F.Z=((a&0xff)==0)  ;              ;                             //      INC     B
RMC15F:                             //RMC15F:
a = B + 1           ;f=a&0xff;B = a                 ;F.Z=((a&0xff)==0)  ;              ;                             //      INC     B
a = B + 1           ;f=a&0xff;B = a                 ;F.Z=((a&0xff)==0)  ;              ;                             //      INC     B
a = B + 1           ;f=a&0xff;B = a                 ;F.Z=((a&0xff)==0)  ;              ;                             //      INC     B
RMC162:                             //RMC162:
a = B - 1           ;f=a&0xff;B = a                 ;F.Z=((a&0xff)==0)  ;              ;                             //      DEC     B
RMC163:                             //RMC163:
a = B - 1           ;f=a&0xff;B = a                 ;F.Z=((a&0xff)==0)  ;              ;                             //      DEC     B
RMC164:                             //RMC164:
                    ;        ;GOS(*(sp++) = (int)&&C164;goto RMC000;C164:a=a;)               ;                             //      CALL    RMC000
                    ;        ;GOS(*(sp++) = (int)&&C167;goto RMC253;C167:a=a;)               ;                             //      CALL    RMC253
                    ;        ;if ( !F.C ) {goto RMC1E5;}else{}               ;                                   //      JR      NC,RMC1E5
                    ;        ;A = MEM[IX+0x03]      ;                                  ;                             //      LD      A,(IX+03h)
a = A + 0x80        ;f=a&0xff;A = a                 ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;                             //      ADD     80h
a = A - 0x7C        ;f=a     ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;                             //      CP      7Ch
                    ;        ;if ( !F.C ) {goto RMC17B;}else{}               ;                                   //      JR      NC,RMC17B
                    ;        ;MEM[IX+0x03] = 0xFC   ;                                  ;                             //      LD      (IX+03h),FCh
                    ;        ;goto RMC137               ;                                  ;                             //      JR      RMC137
RMC17B:                             //RMC17B:
a = A - 0x81        ;f=a     ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;                             //      CP      81h
                    ;        ;if ( !F.C ) {goto RMC189;}else{}               ;                                   //      JR      NC,RMC189
                    ;        ;MEM[IX+0x02] = 0x00   ;                                  ;                             //      LD      (IX+02h),00h
                    ;        ;MEM[IX+0x03] = 0x00   ;                                  ;                             //      LD      (IX+03h),00h
                    ;        ;goto RMC137               ;                                  ;                             //      JR      RMC137
RMC189:                             //RMC189:
                    ;        ;B = MEM[IX+0x01]      ;                                  ;                             //      LD      B,(IX+01h)
                    ;        ;C = MEM[IX+0x00]      ;                                  ;                             //      LD      C,(IX+00h)
a = A - 0x85        ;f=a     ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;                             //      CP      85h
                    ;        ;if (  F.C ) {goto RMC194;}else{}               ;                                   //      JR      C,RMC194
a = B + 1           ;f=a&0xff;B = a                 ;F.Z=((a&0xff)==0)  ;              ;                             //      INC     B
RMC194:                             //RMC194:
a = B + 1           ;f=a&0xff;B = a                 ;F.Z=((a&0xff)==0)  ;              ;                             //      INC     B
                    ;        ;GOS(*(sp++) = (int)&&C195;goto RMC000;C195:a=a;)               ;                             //      CALL    RMC000
                    ;        ;GOS(*(sp++) = (int)&&C198;goto RMC253;C198:a=a;)               ;                             //      CALL    RMC253
                    ;        ;if ( !F.C ) {goto RMC1C5;}else{}               ;                                   //      JR      NC,RMC1C5
                    ;        ;A = 0xFD              ;                                  ;                             //      LD      A,FDh
a = A - MEM[IX+0x02];f=a     ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;                             //      CP      (IX+02h)
                    ;        ;if (  F.C ) {goto RMC1AE;}else{}               ;                                   //      JR      C,RMC1AE
a = C + 1           ;f=a&0xff;C = a                 ;F.Z=((a&0xff)==0)  ;              ;                             //      INC     C
                    ;        ;GOS(*(sp++) = (int)&&C1A5;goto RMC000;C1A5:a=a;)               ;                             //      CALL    RMC000
                    ;        ;GOS(*(sp++) = (int)&&C1A8;goto RMC253;C1A8:a=a;)               ;                             //      CALL    RMC253
                    ;        ;if ( !F.C ) {goto RMC1CB;}else{}               ;                                   //      JR      NC,RMC1CB
a = C - 1           ;f=a&0xff;C = a                 ;F.Z=((a&0xff)==0)  ;              ;                             //      DEC     C
RMC1AE:                             //RMC1AE:
                    ;        ;A = MEM[IX+0x02]      ;                                  ;                             //      LD      A,(IX+02h)
a = A + 0x80        ;f=a&0xff;A = a                 ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;                             //      ADD     80h
a = A - 0x81        ;f=a     ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;                             //      CP      81h
                    ;        ;if ( !F.C ) {goto RMC1C1;}else{}               ;                                   //      JR      NC,RMC1C1
a = C - 1           ;f=a&0xff;C = a                 ;F.Z=((a&0xff)==0)  ;              ;                             //      DEC     C
                    ;        ;GOS(*(sp++) = (int)&&C1B8;goto RMC000;C1B8:a=a;)               ;                             //      CALL    RMC000
                    ;        ;GOS(*(sp++) = (int)&&C1BB;goto RMC253;C1BB:a=a;)               ;                             //      CALL    RMC253
                    ;        ;if ( !F.C ) {goto RMC1D1;}else{}               ;                                   //      JR      NC,RMC1D1
a = C + 1           ;f=a&0xff;C = a                 ;F.Z=((a&0xff)==0)  ;              ;                             //      INC     C
RMC1C1:                             //RMC1C1:
a = B - 1           ;f=a&0xff;B = a                 ;F.Z=((a&0xff)==0)  ;              ;                             //      DEC     B
a = B - 1           ;f=a&0xff;B = a                 ;F.Z=((a&0xff)==0)  ;              ;                             //      DEC     B
                    ;        ;goto RMC194               ;                                  ;                             //      JR      RMC194
RMC1C5:                             //RMC1C5:
                    ;        ;MEM[IX+0x02] = 0x00   ;                                  ;                             //      LD      (IX+02h),00h
                    ;        ;goto RMC1D5               ;                                  ;                             //      JR      RMC1D5
RMC1CB:                             //RMC1CB:
                    ;        ;MEM[IX+0x02] = 0x01   ;                                  ;                             //      LD      (IX+02h),01h
                    ;        ;goto RMC1D5               ;                                  ;                             //      JR      RMC1D5
RMC1D1:                             //RMC1D1:
                    ;        ;MEM[IX+0x02] = 0xFF   ;                                  ;                             //      LD      (IX+02h),FFh
RMC1D5:                             //RMC1D5:
                    ;        ;A = MEM[IX+0x01]      ;                                  ;                             //      LD      A,(IX+01h)
a = A - B           ;f=a     ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;                             //      CP      B
                    ;        ;if ( !F.Z ) {goto RMC164;}else{}               ;                                   //      JR      NZ,RMC164
                    ;        ;MEM[IX+0x03] = 0x00   ;                                  ;                             //      LD      (IX+03h),00h
                    ;        ;goto RMC164               ;                                  ;                             //      JR      RMC164
                    ;        ;a=a                   ;                                  ;                             //      NOP
                    ;        ;a=a                   ;                                  ;                             //      NOP
                    ;        ;a=a                   ;                                  ;                             //      NOP
                    ;        ;a=a                   ;                                  ;                             //      NOP
RMC1E5:                             //RMC1E5:
                    ;        ;MEM[IX+0x00] = C      ;                                  ;                             //      LD      (IX+00h),C
                    ;        ;MEM[IX+0x01] = B      ;                                  ;                             //      LD      (IX+01h),B
                    ;        ;A = MEM[IX+0x04]      ;                                  ;                             //      LD      A,(IX+04h)
a = A - 0x02        ;f=a     ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;                             //      CP      02h
                    ;        ;if (  F.C ) {goto RMC202;}else{}               ;                                   //      JR      C,RMC202
a = B + 1           ;f=a&0xff;B = a                 ;F.Z=((a&0xff)==0)  ;              ;                             //      INC     B
                    ;        ;A = MEM[IX+0x07]      ;                                  ;                             //      LD      A,(IX+07h)
a = A & 0xE0        ;f=a&0xff;A = a                 ;F.Z=((a&0xff)==0)  ;F.C=0         ;                             //      AND     E0h
a = A + 0x08        ;f=a&0xff;A = a                 ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;                             //      ADD     08h
                    ;        ;IO[BC] = A            ;                                  ;                             //      !OUT     (C),A
a = A + 0x10        ;f=a&0xff;A = a                 ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;                             //      ADD     10h
a = C + 1           ;f=a&0xff;C = a                 ;F.Z=((a&0xff)==0)  ;              ;                             //      INC     C
                    ;        ;IO[BC] = A            ;                                  ;                             //      !OUT     (C),A
                    ;        ;RET(goto **(--sp);)         ;                                  ;                             //      RET
RMC202:                             //RMC202:
                    ;        ;D = A                 ;                                  ;                             //      LD      D,A
                    ;        ;A = MEM[IX+0x07]      ;                                  ;                             //      LD      A,(IX+07h)
                    ;        ;IO[BC] = A            ;                                  ;                             //      !OUT     (C),A
a = C + 1           ;f=a&0xff;C = a                 ;F.Z=((a&0xff)==0)  ;              ;                             //      INC     C
a = A + 0x10        ;f=a&0xff;A = a                 ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;                             //      ADD     10h
                    ;        ;IO[BC] = A            ;                                  ;                             //      !OUT     (C),A
                    ;        ;E = A                 ;                                  ;                             //      LD      E,A
                    ;        ;A = D                 ;                                  ;                             //      LD      A,D
a = A - 0x00        ;f=a     ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;                             //      CP      00h
                    ;        ;if ( !F.Z ) {goto RMC23B;}else{}               ;                                   //      JR      NZ,RMC23B
                    ;        ;A = E                 ;                                  ;                             //      LD      A,E
a = A & 0xF0        ;f=a&0xff;A = a                 ;F.Z=((a&0xff)==0)  ;F.C=0         ;                             //      AND     F0h
a = A + 0x03        ;f=a&0xff;A = a                 ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;                             //      ADD     03h
                    ;        ;E = A                 ;                                  ;                             //      LD      E,A
                    ;        ;A = 0x00              ;                                  ;                             //      LD      A,00h
a = A - MEM[IX+0x02];f=a     ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;                             //      CP      (IX+02h)
                    ;        ;if (  F.Z ) {goto RMC230;}else{}               ;                                   //      JR      Z,RMC230
a = A - MEM[IX+0x03];f=a     ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;                             //      CP      (IX+03h)
                    ;        ;if (  F.Z ) {goto RMC230;}else{}               ;                                   //      JR      Z,RMC230
                    ;        ;A = MEM[IX+0x02]      ;                                  ;                             //      LD      A,(IX+02h)
a = A ^ MEM[IX+0x03];f=a&0xff;A = a                 ;F.Z=((a&0xff)==0)  ;F.C=0         ;                             //      XOR     (IX+03h)
a = A - 0x80        ;f=a     ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;                             //      CP      80h
                    ;        ;if (  F.C ) {goto RMC231;}else{}               ;                                   //      JR      C,RMC231
a = E + 1           ;f=a&0xff;E = a                 ;F.Z=((a&0xff)==0)  ;              ;                             //      INC     E
RMC230:                             //RMC230:
a = E + 1           ;f=a&0xff;E = a                 ;F.Z=((a&0xff)==0)  ;              ;                             //      INC     E
RMC231:                             //RMC231:
a = B + 1           ;f=a&0xff;B = a                 ;F.Z=((a&0xff)==0)  ;              ;                             //      INC     B
                    ;        ;A = E                 ;                                  ;                             //      LD      A,E
                    ;        ;IO[BC] = A            ;                                  ;                             //      !OUT     (C),A
a = C - 1           ;f=a&0xff;C = a                 ;F.Z=((a&0xff)==0)  ;              ;                             //      DEC     C
a = A - 0x10        ;f=a     ;A = a                 ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;                             //      SUB     10h
                    ;        ;IO[BC] = A            ;                                  ;                             //      !OUT     (C),A
                    ;        ;RET(goto **(--sp);)         ;                                  ;                             //      RET
RMC23B:                             //RMC23B:
                    ;        ;A = E                 ;                                  ;                             //      LD      A,E
a = A & 0xF0        ;f=a&0xff;A = a                 ;F.Z=((a&0xff)==0)  ;F.C=0         ;                             //      AND     F0h
a = A + 0x06        ;f=a&0xff;A = a                 ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;                             //      ADD     06h
                    ;        ;E = A                 ;                                  ;                             //      LD      E,A
                    ;        ;A = MEM[IX+0x00]      ;                                  ;                             //      LD      A,(IX+00h)
a = A & 0x01        ;f=a&0xff;A = a                 ;F.Z=((a&0xff)==0)  ;F.C=0         ;                             //      AND     01h
                    ;        ;if (  F.Z ) {goto RMC249;}else{}               ;                                   //      JR      Z,RMC249
a = E + 1           ;f=a&0xff;E = a                 ;F.Z=((a&0xff)==0)  ;              ;                             //      INC     E
RMC249:                             //RMC249:
                    ;        ;A = E                 ;                                  ;                             //      LD      A,E
a = B + 1           ;f=a&0xff;B = a                 ;F.Z=((a&0xff)==0)  ;              ;                             //      INC     B
                    ;        ;IO[BC] = A            ;                                  ;                             //      !OUT     (C),A
a = C - 1           ;f=a&0xff;C = a                 ;F.Z=((a&0xff)==0)  ;              ;                             //      DEC     C
a = A - 0x10        ;f=a     ;A = a                 ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;                             //      SUB     10h
                    ;        ;IO[BC] = A            ;                                  ;                             //      !OUT     (C),A
                    ;        ;RET(goto **(--sp);)         ;                                  ;                             //      RET
RMC253:                             //RMC253:
                    ;        ;A = 0x30              ;                                  ;                             //      LD      A,30h
a = A - D           ;f=a     ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;                             //      CP      D
                    ;        ;if (  F.C ) {RET(goto **(--sp););}else{}          ;                                    //      RET     C
a = A - E           ;f=a     ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;                             //      CP      E
                    ;        ;if (  F.C ) {RET(goto **(--sp););}else{}          ;                                    //      RET     C
a = A - H           ;f=a     ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;                             //      CP      H
                    ;        ;if (  F.C ) {RET(goto **(--sp););}else{}          ;                                    //      RET     C
a = A - L           ;f=a     ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;                             //      CP      L
                    ;        ;RET(goto **(--sp);)         ;                                  ;                             //      RET
                    ;        ;a=a                   ;                                  ;                             //      NOP
RMC25E:                             //RMC25E:
                    ;        ;A = 0x00              ;                                  ;                             //      LD      A,00h
                    ;        ;GOS(*(sp++) = (int)&&C260;goto RM001B;C260:a=a;)               ;                             //      CALL    RM001B
a = A - 0x32        ;f=a     ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;                             //      CP      32h
                    ;        ;if (  F.Z ) {goto RMC26C;}else{}               ;                                   //      JR      Z,RMC26C
a = A - 0x38        ;f=a     ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;                             //      CP      38h
                    ;        ;if (  F.Z ) {goto RMC29E;}else{}               ;                                   //      JR      Z,RMC29E
                    ;        ;RET(goto **(--sp);)         ;                                  ;                             //      RET
RMC26C:                             //RMC26C:
                    ;        ;A = MEM[IX+0x04]      ;                                  ;                             //      LD      A,(IX+04h)
a = A - 0x80        ;f=a     ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;                             //      CP      80h
                    ;        ;if (  F.Z ) {RET(goto **(--sp););}else{}          ;                                    //      RET     Z
                    ;        ;A = RMB602[0]             ;                                  ;                             //      LD      A,(RMB602)
a = A + 1           ;f=a&0xff;A = a                 ;F.Z=((a&0xff)==0)  ;              ;                             //      INC     A
a = A - MEM[IX+0x00];f=a     ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;                             //      CP      (IX+00h)
                    ;        ;if ( !F.Z ) {RET(goto **(--sp););}else{}          ;                                    //      RET     NZ
                    ;        ;A = RMB603[0]             ;                                  ;                             //      LD      A,(RMB603)
a = A - 1           ;f=a&0xff;A = a                 ;F.Z=((a&0xff)==0)  ;              ;                             //      DEC     A
a = A - MEM[IX+0x01];f=a     ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;                             //      CP      (IX+01h)
                    ;        ;if ( !F.Z ) {RET(goto **(--sp););}else{}          ;                                    //      RET     NZ
                    ;        ;MEM[IX+0x04] = 0x80   ;                                  ;                             //      LD      (IX+04h),80h
                    ;        ;C = MEM[IX+0x00]      ;                                  ;                             //      LD      C,(IX+00h)
                    ;        ;B = MEM[IX+0x01]      ;                                  ;                             //      LD      B,(IX+01h)
                    ;        ;A = 0x00              ;                                  ;                             //      LD      A,00h
                    ;        ;IO[BC] = A            ;                                  ;                             //      !OUT     (C),A
a = C + 1           ;f=a&0xff;C = a                 ;F.Z=((a&0xff)==0)  ;              ;                             //      INC     C
                    ;        ;IO[BC] = A            ;                                  ;                             //      !OUT     (C),A
a = B + 1           ;f=a&0xff;B = a                 ;F.Z=((a&0xff)==0)  ;              ;                             //      INC     B
                    ;        ;A = 0x58              ;                                  ;                             //      LD      A,58h
                    ;        ;IO[BC] = A            ;                                  ;                             //      !OUT     (C),A
a = C - 1           ;f=a&0xff;C = a                 ;F.Z=((a&0xff)==0)  ;              ;                             //      DEC     C
                    ;        ;A = 0x48              ;                                  ;                             //      LD      A,48h
                    ;        ;IO[BC] = A            ;                                  ;                             //      !OUT     (C),A
                    ;        ;RET(goto **(--sp);)         ;                                  ;                             //      RET
RMC29E:                             //RMC29E:
                    ;        ;A = MEM[IX+0x04]      ;                                  ;                             //      LD      A,(IX+04h)
a = A - 0x80        ;f=a     ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;                             //      CP      80h
                    ;        ;if ( !F.Z ) {RET(goto **(--sp););}else{}          ;                                    //      RET     NZ
                    ;        ;C = RMB602[0];B = RMB602[1]   ;                                  ;                             //      LD      BC,(RMB602)
a = C + 1           ;f=a&0xff;C = a                 ;F.Z=((a&0xff)==0)  ;              ;                             //      INC     C
                    ;        ;A = 0x00              ;                                  ;                             //      LD      A,00h
                    ;        ;IO[BC] = A            ;                                  ;                             //      !OUT     (C),A
a = C + 1           ;f=a&0xff;C = a                 ;F.Z=((a&0xff)==0)  ;              ;                             //      INC     C
                    ;        ;IO[BC] = A            ;                                  ;                             //      !OUT     (C),A
a = C - 1           ;f=a&0xff;C = a                 ;F.Z=((a&0xff)==0)  ;              ;                             //      DEC     C
a = B - 1           ;f=a&0xff;B = a                 ;F.Z=((a&0xff)==0)  ;              ;                             //      DEC     B
                    ;        ;GOS(*(sp++) = (int)&&C2B2;goto RMC000;C2B2:a=a;)               ;                             //      CALL    RMC000
                    ;        ;GOS(*(sp++) = (int)&&C2B5;goto RMC253;C2B5:a=a;)               ;                             //      CALL    RMC253
                    ;        ;if (  F.C ) {RET(goto **(--sp););}else{}          ;                                    //      RET     C
                    ;        ;MEM[IX+0x04] = 0x00   ;                                  ;                             //      LD      (IX+04h),00h
                    ;        ;A = MEM[IX+0x07]      ;                                  ;                             //      LD      A,(IX+07h)
a = A & 0xF0        ;f=a&0xff;A = a                 ;F.Z=((a&0xff)==0)  ;F.C=0         ;                             //      AND     F0h
a = A | 0x01        ;f=a&0xff;A = a                 ;F.Z=((a&0xff)==0)  ;F.C=0         ;                             //      OR      01h
                    ;        ;MEM[IX+0x07] = A      ;                                  ;                             //      LD      (IX+07h),A
                    ;        ;GOS(*(sp++) = (int)&&C2C7;goto RMC1E5;C2C7:a=a;)               ;                             //      CALL    RMC1E5
                    ;        ;RET(goto **(--sp);)         ;                                  ;                             //      RET
RMC2CB:                             //RMC2CB:
                    ;        ;IX = 0xB610             ;                                  ;                             //      LD      IX,B610h
                    ;        ;BC = 0x1C00             ;                                  ;                             //      LD      BC,1C00h
                    ;        ;A = 0x0E              ;                                  ;                             //      LD      A,0Eh
                    ;        ;IO[BC] = A            ;                                  ;                             //      !OUT     (C),A
a = B - 1           ;f=a&0xff;B = a                 ;F.Z=((a&0xff)==0)  ;              ;                             //      DEC     B
a = IO[BC]          ;f=a&0xff;A = a                 ;F.Z=((a&0xff)==0)  ;              ;                             //      !IN      A,(C)
A = InputJoystick();                             ////c:A = InputJoystick();

                    ;        ;MEM[IX+0x06] = A      ;                                  ;                             //      LD      (IX+06h),A
                    ;        ;GOS(*(sp++) = (int)&&C2DC;goto RMC25E;C2DC:a=a;)               ;                             //      CALL    RMC25E
                    ;        ;A = MEM[IX+0x04]      ;                                  ;                             //      LD      A,(IX+04h)
a = A - 0x80        ;f=a     ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;                             //      CP      80h
                    ;        ;if (  F.Z ) {goto RMC318;}else{}               ;                                   //      JR      Z,RMC318
                    ;        ;A = MEM[IX+0x06]      ;                                  ;                             //      LD      A,(IX+06h)
a = A & (1<<0)     ;f=a&0xff;                      ;F.Z=((a&0xff)==0)  ;              ;                             //      BIT     0,A
                    ;        ;if (  F.Z ) {goto RMC2F9;}else{}               ;                                   //      JR      Z,RMC2F9
RMC2ED:                             //RMC2ED:
                    ;        ;A = MEM[IX+0x08]      ;                                  ;                             //      LD      A,(IX+08h)
a = A - 0x0A        ;f=a     ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;                             //      CP      0Ah
                    ;        ;if ( !F.C ) {goto RMC315;}else{}               ;                                   //      JR      NC,RMC315
a = MEM[IX+0x08] + 1;f=a&0xff;MEM[IX+0x08] = a      ;F.Z=((a&0xff)==0)  ;              ;                             //      INC     (IX+08h)
                    ;        ;goto RMC315               ;                                  ;                             //      JR      RMC315
RMC2F9:                             //RMC2F9:
                    ;        ;D = A                 ;                                  ;                             //      LD      D,A
                    ;        ;A = MEM[IX+0x04]      ;                                  ;                             //      LD      A,(IX+04h)
a = A - 0x02        ;f=a     ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;                             //      CP      02h
                    ;        ;if ( !F.C ) {goto RMC2ED;}else{}               ;                                   //      JR      NC,RMC2ED
                    ;        ;A = MEM[IX+0x08]      ;                                  ;                             //      LD      A,(IX+08h)
a = A - 0x02        ;f=a     ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;                             //      CP      02h
                    ;        ;if ( !F.C ) {goto RMC310;}else{}               ;                                   //      JR      NC,RMC310
                    ;        ;A = D                 ;                                  ;                             //      LD      A,D
a = A | 0x01        ;f=a&0xff;A = a                 ;F.Z=((a&0xff)==0)  ;F.C=0         ;                             //      OR      01h
                    ;        ;MEM[IX+0x06] = A      ;                                  ;                             //      LD      (IX+06h),A
                    ;        ;goto RMC315               ;                                  ;                             //      JR      RMC315
RMC310:                             //RMC310:
a = A - 0x02        ;f=a     ;A = a                 ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;                             //      SUB     02h
                    ;        ;MEM[IX+0x08] = A      ;                                  ;                             //      LD      (IX+08h),A
RMC315:                             //RMC315:
                    ;        ;GOS(*(sp++) = (int)&&C315;goto RMC00D;C315:a=a;)               ;                             //      CALL    RMC00D
RMC318:                             //RMC318:
                    ;        ;C = RMB602[0];B = RMB602[1]   ;                                  ;                             //      LD      BC,(RMB602)
                    ;        ;*(SP++)=BC            ;                                  ;                             //      PUSH    BC
                    ;        ;A = 0x00              ;                                  ;                             //      LD      A,00h
a = B + 1           ;f=a&0xff;B = a                 ;F.Z=((a&0xff)==0)  ;              ;                             //      INC     B
                    ;        ;E = 0x04              ;                                  ;                             //      LD      E,04h
RMC322:                             //RMC322:
                    ;        ;IO[BC] = A            ;                                  ;                             //      !OUT     (C),A
a = C + 1           ;f=a&0xff;C = a                 ;F.Z=((a&0xff)==0)  ;              ;                             //      INC     C
a = E - 1           ;f=a&0xff;E = a                 ;F.Z=((a&0xff)==0)  ;              ;                             //      DEC     E
                    ;        ;if ( !F.Z ) {goto RMC322;}else{}               ;                                   //      JR      NZ,RMC322
a = C - 1           ;f=a&0xff;C = a                 ;F.Z=((a&0xff)==0)  ;              ;                             //      DEC     C
a = B - 1           ;f=a&0xff;B = a                 ;F.Z=((a&0xff)==0)  ;              ;                             //      DEC     B
                    ;        ;IO[BC] = A            ;                                  ;                             //      !OUT     (C),A
                    ;        ;BC=*(--SP)            ;                                  ;                             //      POP     BC
                    ;        ;*(SP++)=BC            ;                                  ;                             //      PUSH    BC
                    ;        ;IO[BC] = A            ;                                  ;                             //      !OUT     (C),A
                    ;        ;A = MEM[IX+0x04]      ;                                  ;                             //      LD      A,(IX+04h)
a = A - 0x80        ;f=a     ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;                             //      CP      80h
                    ;        ;HL=*(--SP)            ;                                  ;                             //      POP     HL
                    ;        ;if (  F.Z ) {goto RMC34A;}else{}               ;                                   //      JR      Z,RMC34A
                    ;        ;A = MEM[IX+0x00]      ;                                  ;                             //      LD      A,(IX+00h)
a = A - C           ;f=a     ;A = a                 ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;                             //      SUB     C
a = A - 0x03        ;f=a     ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;                             //      CP      03h
                    ;        ;if ( !F.C ) {goto RMC36E;}else{}               ;                                   //      JR      NC,RMC36E
                    ;        ;A = MEM[IX+0x01]      ;                                  ;                             //      LD      A,(IX+01h)
a = A - B           ;f=a     ;A = a                 ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;                             //      SUB     B
a = A - 0x02        ;f=a     ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;                             //      CP      02h
                    ;        ;if ( !F.Z ) {goto RMC36E;}else{}               ;                                   //      JR      NZ,RMC36E
                    ;        ;goto RMC354               ;                                  ;                             //      JR      RMC354
RMC34A:                             //RMC34A:
                    ;        ;*(SP++)=HL            ;                                  ;                             //      PUSH    HL
                    ;        ;A = 0x00              ;                                  ;                             //      LD      A,00h
a = C + 1           ;f=a&0xff;C = a                 ;F.Z=((a&0xff)==0)  ;              ;                             //      INC     C
                    ;        ;IO[BC] = A            ;                                  ;                             //      !OUT     (C),A
a = C + 1           ;f=a&0xff;C = a                 ;F.Z=((a&0xff)==0)  ;              ;                             //      INC     C
                    ;        ;IO[BC] = A            ;                                  ;                             //      !OUT     (C),A
                    ;        ;BC=*(--SP)            ;                                  ;                             //      POP     BC
RMC354:                             //RMC354:
                    ;        ;A = MEM[IX+0x06]      ;                                  ;                             //      LD      A,(IX+06h)
a = A & (1<<2)     ;f=a&0xff;                      ;F.Z=((a&0xff)==0)  ;              ;                             //      BIT     2,A
                    ;        ;if ( !F.Z ) {goto RMC360;}else{}               ;                                   //      JR      NZ,RMC360
                    ;        ;MEM[IX+0x02] = 0xFF   ;                                  ;                             //      LD      (IX+02h),FFh
a = C - 1           ;f=a&0xff;C = a                 ;F.Z=((a&0xff)==0)  ;              ;                             //      DEC     C
RMC360:                             //RMC360:
a = A & (1<<3)     ;f=a&0xff;                      ;F.Z=((a&0xff)==0)  ;              ;                             //      BIT     3,A
                    ;        ;if ( !F.Z ) {goto RMC369;}else{}               ;                                   //      JR      NZ,RMC369
                    ;        ;MEM[IX+0x02] = 0x01   ;                                  ;                             //      LD      (IX+02h),01h
a = C + 1           ;f=a&0xff;C = a                 ;F.Z=((a&0xff)==0)  ;              ;                             //      INC     C
RMC369:                             //RMC369:
                    ;        ;GOS(*(sp++) = (int)&&C369;goto RMC413;C369:a=a;)               ;                             //      CALL    RMC413
                    ;        ;if ( !F.C ) {goto RMC375;}else{}               ;                                   //      JR      NC,RMC375
RMC36E:                             //RMC36E:
                    ;        ;C = RMB602[0];B = RMB602[1]   ;                                  ;                             //      LD      BC,(RMB602)
                    ;        ;GOS(*(sp++) = (int)&&C372;goto RMC413;C372:a=a;)               ;                             //      CALL    RMC413
RMC375:                             //RMC375:
                    ;        ;RMB602[0] = C;RMB602[1] = B   ;                                  ;                             //      LD      (RMB602),BC
                    ;        ;A = MEM[IX+0x04]      ;                                  ;                             //      LD      A,(IX+04h)
a = A - 0x80        ;f=a     ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;                             //      CP      80h
                    ;        ;if ( !F.Z ) {goto RMC39E;}else{}               ;                                   //      JR      NZ,RMC39E
a = C + 1           ;f=a&0xff;C = a                 ;F.Z=((a&0xff)==0)  ;              ;                             //      INC     C
a = B - 1           ;f=a&0xff;B = a                 ;F.Z=((a&0xff)==0)  ;              ;                             //      DEC     B
                    ;        ;MEM[IX+0x01] = B      ;                                  ;                             //      LD      (IX+01h),B
                    ;        ;MEM[IX+0x00] = C      ;                                  ;                             //      LD      (IX+00h),C
                    ;        ;A = MEM[IX+0x05]      ;                                  ;                             //      LD      A,(IX+05h)
a = A - 0x20        ;f=a     ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;                             //      CP      20h
                    ;        ;if ( !F.C ) {goto RMC393;}else{}               ;                                   //      JR      NC,RMC393
a = A + 1           ;f=a&0xff;A = a                 ;F.Z=((a&0xff)==0)  ;              ;                             //      INC     A
                    ;        ;MEM[IX+0x05] = A      ;                                  ;                             //      LD      (IX+05h),A
RMC393:                             //RMC393:
                    ;        ;A = MEM[IX+0x08]      ;                                  ;                             //      LD      A,(IX+08h)
a = A - 0x0A        ;f=a     ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;                             //      CP      0Ah
                    ;        ;if ( !F.C ) {goto RMC39E;}else{}               ;                                   //      JR      NC,RMC39E
a = A + 1           ;f=a&0xff;A = a                 ;F.Z=((a&0xff)==0)  ;              ;                             //      INC     A
                    ;        ;MEM[IX+0x08] = A      ;                                  ;                             //      LD      (IX+08h),A
RMC39E:                             //RMC39E:
                    ;        ;C = RMB602[0];B = RMB602[1]   ;                                  ;                             //      LD      BC,(RMB602)
                    ;        ;A = 0x69              ;                                  ;                             //      LD      A,69h
                    ;        ;IO[BC] = A            ;                                  ;                             //      !OUT     (C),A
a = C + 1           ;f=a&0xff;C = a                 ;F.Z=((a&0xff)==0)  ;              ;                             //      INC     C
a = C + 1           ;f=a&0xff;C = a                 ;F.Z=((a&0xff)==0)  ;              ;                             //      INC     C
a = C + 1           ;f=a&0xff;C = a                 ;F.Z=((a&0xff)==0)  ;              ;                             //      INC     C
a = A + 0x03        ;f=a&0xff;A = a                 ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;                             //      ADD     03h
                    ;        ;IO[BC] = A            ;                                  ;                             //      !OUT     (C),A
a = B + 1           ;f=a&0xff;B = a                 ;F.Z=((a&0xff)==0)  ;              ;                             //      INC     B
                    ;        ;A = 0x7C              ;                                  ;                             //      LD      A,7Ch
                    ;        ;IO[BC] = A            ;                                  ;                             //      !OUT     (C),A
a = A - 1           ;f=a&0xff;A = a                 ;F.Z=((a&0xff)==0)  ;              ;                             //      DEC     A
a = C - 1           ;f=a&0xff;C = a                 ;F.Z=((a&0xff)==0)  ;              ;                             //      DEC     C
                    ;        ;IO[BC] = A            ;                                  ;                             //      !OUT     (C),A
a = A - 1           ;f=a&0xff;A = a                 ;F.Z=((a&0xff)==0)  ;              ;                             //      DEC     A
a = C - 1           ;f=a&0xff;C = a                 ;F.Z=((a&0xff)==0)  ;              ;                             //      DEC     C
                    ;        ;IO[BC] = A            ;                                  ;                             //      !OUT     (C),A
a = A - 1           ;f=a&0xff;A = a                 ;F.Z=((a&0xff)==0)  ;              ;                             //      DEC     A
a = C - 1           ;f=a&0xff;C = a                 ;F.Z=((a&0xff)==0)  ;              ;                             //      DEC     C
                    ;        ;IO[BC] = A            ;                                  ;                             //      !OUT     (C),A
                    ;        ;A = MEM[IX+0x04]      ;                                  ;                             //      LD      A,(IX+04h)
a = A - 0x80        ;f=a     ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;                             //      CP      80h
                    ;        ;if ( !F.Z ) {RET(goto **(--sp););}else{}          ;                                    //      RET     NZ
a = B - 1           ;f=a&0xff;B = a                 ;F.Z=((a&0xff)==0)  ;              ;                             //      DEC     B
a = C + 1           ;f=a&0xff;C = a                 ;F.Z=((a&0xff)==0)  ;              ;                             //      INC     C
                    ;        ;A = 0x6A              ;                                  ;                             //      LD      A,6Ah
                    ;        ;IO[BC] = A            ;                                  ;                             //      !OUT     (C),A
a = A + 1           ;f=a&0xff;A = a                 ;F.Z=((a&0xff)==0)  ;              ;                             //      INC     A
a = C + 1           ;f=a&0xff;C = a                 ;F.Z=((a&0xff)==0)  ;              ;                             //      INC     C
                    ;        ;IO[BC] = A            ;                                  ;                             //      !OUT     (C),A
                    ;        ;RET(goto **(--sp);)         ;                                  ;                             //      RET
RMC3CF:                             //RMC3CF:
                    ;        ;*(SP++)=BC            ;                                  ;                             //      PUSH    BC
a = B + 1           ;f=a&0xff;B = a                 ;F.Z=((a&0xff)==0)  ;              ;                             //      INC     B
                    ;        ;D = 0x02              ;                                  ;                             //      LD      D,02h
RMC3D3:                             //RMC3D3:
                    ;        ;E = 0x04              ;                                  ;                             //      LD      E,04h
RMC3D5:                             //RMC3D5:
a = IO[BC]          ;f=a&0xff;A = a                 ;F.Z=((a&0xff)==0)  ;              ;                             //      !IN      A,(C)
a = A - 0x30        ;f=a     ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;                             //      CP      30h
                    ;        ;if ( !F.C ) {goto RMC410;}else{}               ;                                   //      JR      NC,RMC410
a = C + 1           ;f=a&0xff;C = a                 ;F.Z=((a&0xff)==0)  ;              ;                             //      INC     C
a = E - 1           ;f=a&0xff;E = a                 ;F.Z=((a&0xff)==0)  ;              ;                             //      DEC     E
                    ;        ;if ( !F.Z ) {goto RMC3D5;}else{}               ;                                   //      JR      NZ,RMC3D5
a = C - 1           ;f=a&0xff;C = a                 ;F.Z=((a&0xff)==0)  ;              ;                             //      DEC     C
a = C - 1           ;f=a&0xff;C = a                 ;F.Z=((a&0xff)==0)  ;              ;                             //      DEC     C
a = C - 1           ;f=a&0xff;C = a                 ;F.Z=((a&0xff)==0)  ;              ;                             //      DEC     C
a = C - 1           ;f=a&0xff;C = a                 ;F.Z=((a&0xff)==0)  ;              ;                             //      DEC     C
a = B + 1           ;f=a&0xff;B = a                 ;F.Z=((a&0xff)==0)  ;              ;                             //      INC     B
a = D - 1           ;f=a&0xff;D = a                 ;F.Z=((a&0xff)==0)  ;              ;                             //      DEC     D
                    ;        ;if ( !F.Z ) {goto RMC3D3;}else{}               ;                                   //      JR      NZ,RMC3D3
                    ;        ;BC=*(--SP)            ;                                  ;                             //      POP     BC
                    ;        ;*(SP++)=BC            ;                                  ;                             //      PUSH    BC
a = IO[BC]          ;f=a&0xff;A = a                 ;F.Z=((a&0xff)==0)  ;              ;                             //      !IN      A,(C)
a = A - 0x30        ;f=a     ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;                             //      CP      30h
                    ;        ;if ( !F.C ) {goto RMC410;}else{}               ;                                   //      JR      NC,RMC410
a = C + 1           ;f=a&0xff;C = a                 ;F.Z=((a&0xff)==0)  ;              ;                             //      INC     C
a = C + 1           ;f=a&0xff;C = a                 ;F.Z=((a&0xff)==0)  ;              ;                             //      INC     C
a = C + 1           ;f=a&0xff;C = a                 ;F.Z=((a&0xff)==0)  ;              ;                             //      INC     C
a = IO[BC]          ;f=a&0xff;A = a                 ;F.Z=((a&0xff)==0)  ;              ;                             //      !IN      A,(C)
a = A - 0x30        ;f=a     ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;                             //      CP      30h
                    ;        ;if ( !F.C ) {goto RMC410;}else{}               ;                                   //      JR      NC,RMC410
                    ;        ;A = MEM[IX+0x04]      ;                                  ;                             //      LD      A,(IX+04h)
a = A - 0x80        ;f=a     ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;                             //      CP      80h
                    ;        ;if ( !F.Z ) {goto RMC40D;}else{}               ;                                   //      JR      NZ,RMC40D
a = C - 1           ;f=a&0xff;C = a                 ;F.Z=((a&0xff)==0)  ;              ;                             //      DEC     C
a = IO[BC]          ;f=a&0xff;A = a                 ;F.Z=((a&0xff)==0)  ;              ;                             //      !IN      A,(C)
a = A - 0x30        ;f=a     ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;                             //      CP      30h
                    ;        ;if ( !F.C ) {goto RMC410;}else{}               ;                                   //      JR      NC,RMC410
a = C - 1           ;f=a&0xff;C = a                 ;F.Z=((a&0xff)==0)  ;              ;                             //      DEC     C
a = IO[BC]          ;f=a&0xff;A = a                 ;F.Z=((a&0xff)==0)  ;              ;                             //      !IN      A,(C)
a = A - 0x30        ;f=a     ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;                             //      CP      30h
                    ;        ;if ( !F.C ) {goto RMC410;}else{}               ;                                   //      JR      NC,RMC410
RMC40D:                             //RMC40D:
                    ;        ;BC=*(--SP)            ;                                  ;                             //      POP     BC
a = A & A           ;f=a&0xff;A = a                 ;F.Z=((a&0xff)==0)  ;F.C=0         ;                             //      AND     A
                    ;        ;RET(goto **(--sp);)         ;                                  ;                             //      RET
RMC410:                             //RMC410:
                    ;        ;BC=*(--SP)            ;                                  ;                             //      POP     BC
                    ;f=-1    ;                      ;                   ;F.C=1         ;                             //      SCF
                    ;        ;RET(goto **(--sp);)         ;                                  ;                             //      RET
RMC413:                             //RMC413:
a = B + 1           ;f=a&0xff;B = a                 ;F.Z=((a&0xff)==0)  ;              ;                             //      INC     B
                    ;        ;GOS(*(sp++) = (int)&&C414;goto RMC3CF;C414:a=a;)               ;                             //      CALL    RMC3CF
                    ;        ;if ( !F.C ) {RET(goto **(--sp););}else{}          ;                                    //      RET     NC
a = B - 1           ;f=a&0xff;B = a                 ;F.Z=((a&0xff)==0)  ;              ;                             //      DEC     B
                    ;        ;GOS(*(sp++) = (int)&&C419;goto RMC3CF;C419:a=a;)               ;                             //      CALL    RMC3CF
                    ;        ;if ( !F.C ) {RET(goto **(--sp););}else{}          ;                                    //      RET     NC
a = B - 1           ;f=a&0xff;B = a                 ;F.Z=((a&0xff)==0)  ;              ;                             //      DEC     B
                    ;        ;GOS(*(sp++) = (int)&&C41E;goto RMC3CF;C41E:a=a;)               ;                             //      CALL    RMC3CF
                    ;        ;if ( !F.C ) {RET(goto **(--sp););}else{}          ;                                    //      RET     NC
a = B + 1           ;f=a&0xff;B = a                 ;F.Z=((a&0xff)==0)  ;              ;                             //      INC     B
                    ;f=-1    ;                      ;                   ;F.C=1         ;                             //      SCF
                    ;        ;RET(goto **(--sp);)         ;                                  ;                             //      RET
                    ;        ;a=a                   ;                                  ;                             //      NOP
RMC426:                             //RMC426:
a = A - MEM[IY+0x01];f=a     ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;                             //      CP      (IY+01h)
                    ;        ;if (  F.Z ) {RET(goto **(--sp););}else{}          ;                                    //      RET     Z
a = IY + DE         ;f=a     ;IY = a                ;                   ;F.C=a>>16     ;                             //      ADD     IY,DE
a = H - 1           ;f=a&0xff;H = a                 ;F.Z=((a&0xff)==0)  ;              ;                             //      DEC     H
                    ;        ;if (  F.Z ) {RET(goto **(--sp););}else{}          ;                                    //      RET     Z
                    ;        ;goto RMC426               ;                                  ;                             //      JR      RMC426
RMC430:                             //RMC430:
                    ;        ;A = RMB610[0]             ;                                  ;                             //      LD      A,(RMB610)
a = A - 0x28        ;f=a     ;A = a                 ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;                             //      SUB     28h
                    ;        ;if ( !F.C ) {goto RMC439;}else{}               ;                                   //      JR      NC,RMC439
                    ;        ;A = 0x00              ;                                  ;                             //      LD      A,00h
RMC439:                             //RMC439:
a = A - MEM[IX+0x0A];f=a     ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;                             //      CP      (IX+0Ah)
                    ;        ;if (  F.C ) {goto RMC46E;}else{}               ;                                   //      JR      C,RMC46E
                    ;        ;A = RMB602[0]             ;                                  ;                             //      LD      A,(RMB602)
a = A - 0x28        ;f=a     ;A = a                 ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;                             //      SUB     28h
                    ;        ;if ( !F.C ) {goto RMC447;}else{}               ;                                   //      JR      NC,RMC447
                    ;        ;A = 0x00              ;                                  ;                             //      LD      A,00h
RMC447:                             //RMC447:
a = A - MEM[IX+0x0A];f=a     ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;                             //      CP      (IX+0Ah)
                    ;        ;if (  F.C ) {goto RMC473;}else{}               ;                                   //      JR      C,RMC473
                    ;        ;A = MEM[IX+0x0A]      ;                                  ;                             //      LD      A,(IX+0Ah)
a = A - MEM[IX+0x00];f=a     ;A = a                 ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;                             //      SUB     (IX+00h)
                    ;        ;if (  F.C ) {goto RMC45B;}else{}               ;                                   //      JR      C,RMC45B
a = A - 0x14        ;f=a     ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;                             //      CP      14h
                    ;        ;if (  F.C ) {RET(goto **(--sp););}else{}          ;                                    //      RET     C
                    ;        ;D = 0xF7              ;                                  ;                             //      LD      D,F7h
                    ;        ;goto RMC45D               ;                                  ;                             //      JR      RMC45D
RMC45B:                             //RMC45B:
                    ;        ;D = 0xFB              ;                                  ;                             //      LD      D,FBh
RMC45D:                             //RMC45D:
                    ;        ;A = MEM[IX+0x08]      ;                                  ;                             //      LD      A,(IX+08h)
a = A & 0x04        ;f=a&0xff;A = a                 ;F.Z=((a&0xff)==0)  ;F.C=0         ;                             //      AND     04h
                    ;        ;A = D                 ;                                  ;                             //      LD      A,D
                    ;        ;if (  F.Z ) {goto RMC467;}else{}               ;                                   //      JR      Z,RMC467
a = A & 0xFE        ;f=a&0xff;A = a                 ;F.Z=((a&0xff)==0)  ;F.C=0         ;                             //      AND     FEh
RMC467:                             //RMC467:
                    ;        ;MEM[IX+0x06] = A      ;                                  ;                             //      LD      (IX+06h),A
a = MEM[IX+0x08] + 1;f=a&0xff;MEM[IX+0x08] = a      ;F.Z=((a&0xff)==0)  ;              ;                             //      INC     (IX+08h)
                    ;        ;RET(goto **(--sp);)         ;                                  ;                             //      RET
RMC46E:                             //RMC46E:
                    ;        ;L = RMB610[0];H = RMB610[1]   ;                                  ;                             //      LD      HL,(RMB610)
                    ;        ;goto RMC476               ;                                  ;                             //      JR      RMC476
RMC473:                             //RMC473:
                    ;        ;L = RMB602[0];H = RMB602[1]   ;                                  ;                             //      LD      HL,(RMB602)
RMC476:                             //RMC476:
                    ;        ;B = MEM[IX+0x01]      ;                                  ;                             //      LD      B,(IX+01h)
                    ;        ;C = MEM[IX+0x00]      ;                                  ;                             //      LD      C,(IX+00h)
                    ;        ;A = L                 ;                                  ;                             //      LD      A,L
a = A - C           ;f=a     ;A = a                 ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;                             //      SUB     C
                    ;        ;D = A                 ;                                  ;                             //      LD      D,A
                    ;        ;E = 0x00              ;                                  ;                             //      LD      E,00h
                    ;        ;if (  F.C ) {goto RMC4D1;}else{}               ;                                   //      JR      C,RMC4D1
                    ;        ;A = B                 ;                                  ;                             //      LD      A,B
a = A - H           ;f=a     ;A = a                 ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;                             //      SUB     H
                    ;        ;E = A                 ;                                  ;                             //      LD      E,A
                    ;        ;if (  F.C ) {goto RMC48D;}else{}               ;                                   //      JR      C,RMC48D
a = A - D           ;f=a     ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;                             //      CP      D
                    ;        ;if ( !F.C ) {goto RMC4D1;}else{}               ;                                   //      JR      NC,RMC4D1
                    ;        ;goto RMC492               ;                                  ;                             //      JR      RMC492
RMC48D:                             //RMC48D:
a = A               ;f=a     ;A = -a                ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;                             //      NEG
a = A - D           ;f=a     ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;                             //      CP      D
                    ;        ;if ( !F.C ) {goto RMC4D1;}else{}               ;                                   //      JR      NC,RMC4D1
RMC492:                             //RMC492:
a = MEM[IX+0x08] + 1;f=a&0xff;MEM[IX+0x08] = a      ;F.Z=((a&0xff)==0)  ;              ;                             //      INC     (IX+08h)
                    ;        ;A = MEM[IX+0x08]      ;                                  ;                             //      LD      A,(IX+08h)
a = A & 0x03        ;f=a&0xff;A = a                 ;F.Z=((a&0xff)==0)  ;F.C=0         ;                             //      AND     03h
                    ;        ;if ( !F.Z ) {goto RMC4E5;}else{}               ;                                   //      JR      NZ,RMC4E5
a = rand()          ;f=a&0xff;A = a                 ;F.Z=((a&0xff)==0)  ;              ;                             //      LD      A,R
a = A               ;f=a&0xff;A=(a>>1)|((a<<7)&0xff);F.Z=((a&0xff)==0)  ;F.C=a&1       ;                             //      RRC     A
a = A               ;f=a&0xff;A=(a>>1)|((a<<7)&0xff);F.Z=((a&0xff)==0)  ;F.C=a&1       ;                             //      RRC     A
a = A               ;f=a&0xff;A=(a>>1)|((a<<7)&0xff);F.Z=((a&0xff)==0)  ;F.C=a&1       ;                             //      RRC     A
a = A               ;f=a&0xff;A=(a>>1)|((a<<7)&0xff);F.Z=((a&0xff)==0)  ;F.C=a&1       ;                             //      RRC     A
a = A & 0x03        ;f=a&0xff;A = a                 ;F.Z=((a&0xff)==0)  ;F.C=0         ;                             //      AND     03h
a = A + 1           ;f=a&0xff;A = a                 ;F.Z=((a&0xff)==0)  ;              ;                             //      INC     A
                    ;        ;MEM[IX+0x08] = A      ;                                  ;                             //      LD      (IX+08h),A
a = rand()          ;f=a&0xff;A = a                 ;F.Z=((a&0xff)==0)  ;              ;                             //      LD      A,R
a = A & (1<<1)     ;f=a&0xff;                      ;F.Z=((a&0xff)==0)  ;              ;                             //      BIT     1,A
                    ;        ;if (  F.Z ) {goto RMC4BE;}else{}               ;                                   //      JR      Z,RMC4BE
a = A & (1<<2)     ;f=a&0xff;                      ;F.Z=((a&0xff)==0)  ;              ;                             //      BIT     2,A
                    ;        ;if (  F.Z ) {goto RMC4BA;}else{}               ;                                   //      JR      Z,RMC4BA
                    ;        ;A = 0xFB              ;                                  ;                             //      LD      A,FBh
                    ;        ;goto RMC4C0               ;                                  ;                             //      JR      RMC4C0
RMC4BA:                             //RMC4BA:
                    ;        ;A = 0xFF              ;                                  ;                             //      LD      A,FFh
                    ;        ;goto RMC4C0               ;                                  ;                             //      JR      RMC4C0
RMC4BE:                             //RMC4BE:
                    ;        ;A = 0xF7              ;                                  ;                             //      LD      A,F7h
RMC4C0:                             //RMC4C0:
                    ;        ;a=A;A=_A;_A=a;                                           ;                             //      EX      AF,AF'
a = rand()          ;f=a&0xff;A = a                 ;F.Z=((a&0xff)==0)  ;              ;                             //      LD      A,R
a = A & (1<<3)     ;f=a&0xff;                      ;F.Z=((a&0xff)==0)  ;              ;                             //      BIT     3,A
                    ;        ;if (  F.Z ) {goto RMC4CB;}else{}               ;                                   //      JR      Z,RMC4CB
                    ;        ;a=A;A=_A;_A=a;                                           ;                             //      EX      AF,AF'
a = A & 0xFE        ;f=a&0xff;A = a                 ;F.Z=((a&0xff)==0)  ;F.C=0         ;                             //      AND     FEh
                    ;        ;a=A;A=_A;_A=a;                                           ;                             //      EX      AF,AF'
RMC4CB:                             //RMC4CB:
                    ;        ;a=A;A=_A;_A=a;                                           ;                             //      EX      AF,AF'
                    ;        ;MEM[IX+0x06] = A      ;                                  ;                             //      LD      (IX+06h),A
                    ;        ;goto RMC4E5               ;                                  ;                             //      JR      RMC4E5
RMC4D1:                             //RMC4D1:
a = MEM[IX+0x08] + 1;f=a&0xff;MEM[IX+0x08] = a      ;F.Z=((a&0xff)==0)  ;              ;                             //      INC     (IX+08h)
                    ;        ;A = MEM[IX+0x08]      ;                                  ;                             //      LD      A,(IX+08h)
a = A & 0x04        ;f=a&0xff;A = a                 ;F.Z=((a&0xff)==0)  ;F.C=0         ;                             //      AND     04h
                    ;        ;if (  F.Z ) {goto RMC4E1;}else{}               ;                                   //      JR      Z,RMC4E1
                    ;        ;MEM[IX+0x06] = 0xFF   ;                                  ;                             //      LD      (IX+06h),FFh
                    ;        ;goto RMC4E5               ;                                  ;                             //      JR      RMC4E5
RMC4E1:                             //RMC4E1:
                    ;        ;MEM[IX+0x06] = 0xFA   ;                                  ;                             //      LD      (IX+06h),FAh
RMC4E5:                             //RMC4E5:
                    ;        ;A = D                 ;                                  ;                             //      LD      A,D
a = A - 0x80        ;f=a     ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;                             //      CP      80h
                    ;        ;if ( !F.C ) {RET(goto **(--sp););}else{}          ;                                    //      RET     NC
a = rand()          ;f=a&0xff;A = a                 ;F.Z=((a&0xff)==0)  ;              ;                             //      LD      A,R
a = A & 0xDE        ;f=a&0xff;A = a                 ;F.Z=((a&0xff)==0)  ;F.C=0         ;                             //      AND     DEh
                    ;        ;if ( !F.Z ) {goto RMC4FD;}else{}               ;                                   //      JR      NZ,RMC4FD
                    ;        ;A = E                 ;                                  ;                             //      LD      A,E
a = A - 0x80        ;f=a     ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;                             //      CP      80h
                    ;        ;if ( !F.C ) {goto RMC4F8;}else{}               ;                                   //      JR      NC,RMC4F8
                    ;        ;L = 0xFF              ;                                  ;                             //      LD      L,FFh
                    ;        ;goto RMC504               ;                                  ;                             //      JR      RMC504
RMC4F8:                             //RMC4F8:
                    ;        ;L = 0x01              ;                                  ;                             //      LD      L,01h
a = C + 1           ;f=a&0xff;C = a                 ;F.Z=((a&0xff)==0)  ;              ;                             //      INC     C
                    ;        ;goto RMC504               ;                                  ;                             //      JR      RMC504
RMC4FD:                             //RMC4FD:
a = rand()          ;f=a&0xff;A = a                 ;F.Z=((a&0xff)==0)  ;              ;                             //      LD      A,R
a = A & 0x3E        ;f=a&0xff;A = a                 ;F.Z=((a&0xff)==0)  ;F.C=0         ;                             //      AND     3Eh
                    ;        ;if ( !F.Z ) {RET(goto **(--sp););}else{}          ;                                    //      RET     NZ
                    ;        ;L = 0x00              ;                                  ;                             //      LD      L,00h
RMC504:                             //RMC504:
                    ;        ;A = MEM[IX+0x04]      ;                                  ;                             //      LD      A,(IX+04h)
a = A - 0x02        ;f=a     ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;                             //      CP      02h
                    ;        ;if ( !F.C ) {RET(goto **(--sp););}else{}          ;                                    //      RET     NC
                    ;        ;IY = 0xBA30             ;                                  ;                             //      LD      IY,BA30h
                    ;        ;DE = 0x0004             ;                                  ;                             //      LD      DE,0004h
                    ;        ;H = 0x14              ;                                  ;                             //      LD      H,14h
                    ;        ;A = 0x00              ;                                  ;                             //      LD      A,00h
                    ;        ;GOS(*(sp++) = (int)&&C515;goto RMC426;C515:a=a;)               ;                             //      CALL    RMC426
a = A - H           ;f=a     ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;                             //      CP      H
                    ;        ;if (  F.Z ) {RET(goto **(--sp););}else{}          ;                                    //      RET     Z
                    ;        ;A = MEM[IX+0x07]      ;                                  ;                             //      LD      A,(IX+07h)
a = A & 0xF0        ;f=a&0xff;A = a                 ;F.Z=((a&0xff)==0)  ;F.C=0         ;                             //      AND     F0h
a = A + L           ;f=a&0xff;A = a                 ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;                             //      ADD     L
a = A + 1           ;f=a&0xff;A = a                 ;F.Z=((a&0xff)==0)  ;              ;                             //      INC     A
                    ;        ;MEM[IX+0x07] = A      ;                                  ;                             //      LD      (IX+07h),A
                    ;        ;MEM[IY+0x00] = C      ;                                  ;                             //      LD      (IY+00h),C
                    ;        ;MEM[IY+0x01] = B      ;                                  ;                             //      LD      (IY+01h),B
                    ;        ;*(SP++)=AF            ;                                  ;                             //      PUSH    AF
                    ;        ;A = 0x12              ;                                  ;                             //      LD      A,12h
a = A + L           ;f=a&0xff;A = a                 ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;                             //      ADD     L
                    ;        ;MEM[IY+0x02] = A      ;                                  ;                             //      LD      (IY+02h),A
                    ;        ;AF=*(--SP)            ;                                  ;                             //      POP     AF
                    ;        ;MEM[IY+0x03] = 0x10   ;                                  ;                             //      LD      (IY+03h),10h
a = L - 1           ;f=a&0xff;L = a                 ;F.Z=((a&0xff)==0)  ;              ;                             //      DEC     L
                    ;        ;if ( !F.Z ) {goto RMC53A;}else{}               ;                                   //      JR      NZ,RMC53A
a = C - 1           ;f=a&0xff;C = a                 ;F.Z=((a&0xff)==0)  ;              ;                             //      DEC     C
RMC53A:                             //RMC53A:
                    ;        ;IO[BC] = A            ;                                  ;                             //      !OUT     (C),A
a = C + 1           ;f=a&0xff;C = a                 ;F.Z=((a&0xff)==0)  ;              ;                             //      INC     C
a = A + 1           ;f=a&0xff;A = a                 ;F.Z=((a&0xff)==0)  ;              ;                             //      INC     A
                    ;        ;IO[BC] = A            ;                                  ;                             //      !OUT     (C),A
                    ;        ;RET(goto **(--sp);)         ;                                  ;                             //      RET
RMC541:                             //RMC541:
                    ;        ;IX = 0xB640             ;                                  ;                             //      LD      IX,B640h
                    ;        ;B = 0x3C              ;                                  ;                             //      LD      B,3Ch
                    ;        ;DE = 0x0010             ;                                  ;                             //      LD      DE,0010h
RMC54A:                             //RMC54A:
                    ;        ;A = MEM[IX+0x01]      ;                                  ;                             //      LD      A,(IX+01h)
a = A - 0x00        ;f=a     ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;                             //      CP      00h
                    ;        ;if (  F.Z ) {goto RMC558;}else{}               ;                                   //      JR      Z,RMC558
                    ;        ;*(SP++)=DE            ;                                  ;                             //      PUSH    DE
                    ;        ;*(SP++)=BC            ;                                  ;                             //      PUSH    BC
                    ;        ;GOS(*(sp++) = (int)&&C553;goto RMC430;C553:a=a;)               ;                             //      CALL    RMC430
                    ;        ;BC=*(--SP)            ;                                  ;                             //      POP     BC
                    ;        ;DE=*(--SP)            ;                                  ;                             //      POP     DE
RMC558:                             //RMC558:
a = IX + DE         ;f=a     ;IX = a                ;                   ;F.C=a>>16     ;                             //      ADD     IX,DE
                    ;        ;if ( --B > 0 ) {goto RMC54A;}else{}             ;                                    //      DJNZ    RMC54A
                    ;        ;RET(goto **(--sp);)         ;                                  ;                             //      RET
RMC55D:                             //RMC55D:
                    ;        ;IX = 0xB640             ;                                  ;                             //      LD      IX,B640h
                    ;        ;B = 0x3C              ;                                  ;                             //      LD      B,3Ch
                    ;        ;DE = 0x0010             ;                                  ;                             //      LD      DE,0010h
RMC566:                             //RMC566:
                    ;        ;A = MEM[IX+0x01]      ;                                  ;                             //      LD      A,(IX+01h)
a = A - 0x00        ;f=a     ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;                             //      CP      00h
                    ;        ;if (  F.Z ) {goto RMC574;}else{}               ;                                   //      JR      Z,RMC574
                    ;        ;*(SP++)=DE            ;                                  ;                             //      PUSH    DE
                    ;        ;*(SP++)=BC            ;                                  ;                             //      PUSH    BC
                    ;        ;GOS(*(sp++) = (int)&&C56F;goto RMC00D;C56F:a=a;)               ;                             //      CALL    RMC00D
                    ;        ;BC=*(--SP)            ;                                  ;                             //      POP     BC
                    ;        ;DE=*(--SP)            ;                                  ;                             //      POP     DE
RMC574:                             //RMC574:
a = IX + DE         ;f=a     ;IX = a                ;                   ;F.C=a>>16     ;                             //      ADD     IX,DE
                    ;        ;if ( --B > 0 ) {goto RMC566;}else{}             ;                                    //      DJNZ    RMC566
                    ;        ;RET(goto **(--sp);)         ;                                  ;                             //      RET
                    ;        ;a=a                   ;                                  ;                             //      NOP
RMC57A:                             //RMC57A:
                    ;        ;IX = 0xB640             ;                                  ;                             //      LD      IX,B640h
                    ;        ;B = 0x08              ;                                  ;                             //      LD      B,08h
                    ;        ;DE = 0x0010             ;                                  ;                             //      LD      DE,0010h
RMC583:                             //RMC583:
                    ;        ;A = RMB615[0]             ;                                  ;                             //      LD      A,(RMB615)
a = A - 0x10        ;f=a     ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;                             //      CP      10h
                    ;        ;if ( !F.C ) {goto RMC58F;}else{}               ;                                   //      JR      NC,RMC58F
                    ;        ;A = RMB610[0]             ;                                  ;                             //      LD      A,(RMB610)
                    ;        ;goto RMC598               ;                                  ;                             //      JR      RMC598
RMC58F:                             //RMC58F:
                    ;        ;A = MEM[IX+0x0A]      ;                                  ;                             //      LD      A,(IX+0Ah)
a = A - MEM[IX+0x0B];f=a     ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;                             //      CP      (IX+0Bh)
                    ;        ;if (  F.Z ) {goto RMC598;}else{}               ;                                   //      JR      Z,RMC598
a = A - 1           ;f=a&0xff;A = a                 ;F.Z=((a&0xff)==0)  ;              ;                             //      DEC     A
RMC598:                             //RMC598:
                    ;        ;MEM[IX+0x0A] = A      ;                                  ;                             //      LD      (IX+0Ah),A
                    ;        ;*(SP++)=BC            ;                                  ;                             //      PUSH    BC
                    ;        ;*(SP++)=DE            ;                                  ;                             //      PUSH    DE
                    ;        ;*(SP++)=AF            ;                                  ;                             //      PUSH    AF
                    ;        ;GOS(*(sp++) = (int)&&C59E;goto RMC430;C59E:a=a;)               ;                             //      CALL    RMC430
                    ;        ;AF=*(--SP)            ;                                  ;                             //      POP     AF
                    ;        ;DE=*(--SP)            ;                                  ;                             //      POP     DE
                    ;        ;BC=*(--SP)            ;                                  ;                             //      POP     BC
a = IX + DE         ;f=a     ;IX = a                ;                   ;F.C=a>>16     ;                             //      ADD     IX,DE
                    ;        ;if ( --B > 0 ) {goto RMC583;}else{}             ;                                    //      DJNZ    RMC583
                    ;        ;RET(goto **(--sp);)         ;                                  ;                             //      RET
RMC5A9:                             //RMC5A9:
                    ;        ;MEM[IX+0x01] = 0x00   ;                                  ;                             //      LD      (IX+01h),00h
                    ;        ;A = 0x2F              ;                                  ;                             //      LD      A,2Fh
                    ;        ;GOS(*(sp++) = (int)&&C5AF;goto RMC5E3;C5AF:a=a;)               ;                             //      CALL    RMC5E3
a = B - 1           ;f=a&0xff;B = a                 ;F.Z=((a&0xff)==0)  ;              ;                             //      DEC     B
                    ;        ;A = 0x2B              ;                                  ;                             //      LD      A,2Bh
                    ;        ;GOS(*(sp++) = (int)&&C5B5;goto RMC5E3;C5B5:a=a;)               ;                             //      CALL    RMC5E3
a = C + 1           ;f=a&0xff;C = a                 ;F.Z=((a&0xff)==0)  ;              ;                             //      INC     C
                    ;        ;A = 0x26              ;                                  ;                             //      LD      A,26h
                    ;        ;GOS(*(sp++) = (int)&&C5BB;goto RMC5E3;C5BB:a=a;)               ;                             //      CALL    RMC5E3
a = B + 1           ;f=a&0xff;B = a                 ;F.Z=((a&0xff)==0)  ;              ;                             //      INC     B
                    ;        ;A = 0x2D              ;                                  ;                             //      LD      A,2Dh
                    ;        ;GOS(*(sp++) = (int)&&C5C1;goto RMC5E3;C5C1:a=a;)               ;                             //      CALL    RMC5E3
a = B + 1           ;f=a&0xff;B = a                 ;F.Z=((a&0xff)==0)  ;              ;                             //      INC     B
                    ;        ;A = 0x24              ;                                  ;                             //      LD      A,24h
                    ;        ;GOS(*(sp++) = (int)&&C5C7;goto RMC5E3;C5C7:a=a;)               ;                             //      CALL    RMC5E3
a = C - 1           ;f=a&0xff;C = a                 ;F.Z=((a&0xff)==0)  ;              ;                             //      DEC     C
                    ;        ;A = 0x2E              ;                                  ;                             //      LD      A,2Eh
                    ;        ;GOS(*(sp++) = (int)&&C5CD;goto RMC5E3;C5CD:a=a;)               ;                             //      CALL    RMC5E3
a = C - 1           ;f=a&0xff;C = a                 ;F.Z=((a&0xff)==0)  ;              ;                             //      DEC     C
                    ;        ;A = 0x28              ;                                  ;                             //      LD      A,28h
                    ;        ;GOS(*(sp++) = (int)&&C5D3;goto RMC5E3;C5D3:a=a;)               ;                             //      CALL    RMC5E3
a = B - 1           ;f=a&0xff;B = a                 ;F.Z=((a&0xff)==0)  ;              ;                             //      DEC     B
                    ;        ;A = 0x2C              ;                                  ;                             //      LD      A,2Ch
                    ;        ;GOS(*(sp++) = (int)&&C5D9;goto RMC5E3;C5D9:a=a;)               ;                             //      CALL    RMC5E3
a = B - 1           ;f=a&0xff;B = a                 ;F.Z=((a&0xff)==0)  ;              ;                             //      DEC     B
                    ;        ;A = 0x2A              ;                                  ;                             //      LD      A,2Ah
                    ;        ;GOS(*(sp++) = (int)&&C5DF;goto RMC5E3;C5DF:a=a;)               ;                             //      CALL    RMC5E3
                    ;        ;RET(goto **(--sp);)         ;                                  ;                             //      RET
RMC5E3:                             //RMC5E3:
                    ;        ;D = A                 ;                                  ;                             //      LD      D,A
a = IO[BC]          ;f=a&0xff;A = a                 ;F.Z=((a&0xff)==0)  ;              ;                             //      !IN      A,(C)
a = A - 0x30        ;f=a     ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;                             //      CP      30h
                    ;        ;if ( !F.C ) {RET(goto **(--sp););}else{}          ;                                    //      RET     NC
                    ;        ;A = D                 ;                                  ;                             //      LD      A,D
                    ;        ;IO[BC] = A            ;                                  ;                             //      !OUT     (C),A
                    ;        ;IY = 0xBB00             ;                                  ;                             //      LD      IY,BB00h
                    ;        ;DE = 0x0004             ;                                  ;                             //      LD      DE,0004h
                    ;        ;H = 0xFF              ;                                  ;                             //      LD      H,FFh
                    ;        ;*(SP++)=AF            ;                                  ;                             //      PUSH    AF
                    ;        ;A = 0x00              ;                                  ;                             //      LD      A,00h
                    ;        ;GOS(*(sp++) = (int)&&C5F8;goto RMC426;C5F8:a=a;)               ;                             //      CALL    RMC426
                    ;        ;AF=*(--SP)            ;                                  ;                             //      POP     AF
                    ;        ;MEM[IY+0x00] = C      ;                                  ;                             //      LD      (IY+00h),C
                    ;        ;MEM[IY+0x01] = B      ;                                  ;                             //      LD      (IY+01h),B
                    ;        ;MEM[IY+0x02] = A      ;                                  ;                             //      LD      (IY+02h),A
                    ;        ;MEM[IY+0x03] = 0x20   ;                                  ;                             //      LD      (IY+03h),20h
                    ;        ;RET(goto **(--sp);)         ;                                  ;                             //      RET
RMC60A:                             //RMC60A:
                    ;        ;IX = 0xBF00             ;                                  ;                             //      LD      IX,BF00h
                    ;        ;DE = 0x0004             ;                                  ;                             //      LD      DE,0004h
                    ;        ;B = 0x20              ;                                  ;                             //      LD      B,20h
RMC613:                             //RMC613:
                    ;        ;A = MEM[IX+0x01]      ;                                  ;                             //      LD      A,(IX+01h)
a = A - 0x00        ;f=a     ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;                             //      CP      00h
                    ;        ;if (  F.Z ) {goto RMC621;}else{}               ;                                   //      JR      Z,RMC621
                    ;        ;*(SP++)=BC            ;                                  ;                             //      PUSH    BC
                    ;        ;*(SP++)=DE            ;                                  ;                             //      PUSH    DE
                    ;        ;GOS(*(sp++) = (int)&&C61C;goto RMC626;C61C:a=a;)               ;                             //      CALL    RMC626
                    ;        ;DE=*(--SP)            ;                                  ;                             //      POP     DE
                    ;        ;BC=*(--SP)            ;                                  ;                             //      POP     BC
RMC621:                             //RMC621:
a = IX + DE         ;f=a     ;IX = a                ;                   ;F.C=a>>16     ;                             //      ADD     IX,DE
                    ;        ;if ( --B > 0 ) {goto RMC613;}else{}             ;                                    //      DJNZ    RMC613
                    ;        ;RET(goto **(--sp);)         ;                                  ;                             //      RET
RMC626:                             //RMC626:
a = rand()          ;f=a&0xff;A = a                 ;F.Z=((a&0xff)==0)  ;              ;                             //      LD      A,R
a = A & 0xD1        ;f=a&0xff;A = a                 ;F.Z=((a&0xff)==0)  ;F.C=0         ;                             //      AND     D1h
                    ;        ;if ( !F.Z ) {RET(goto **(--sp););}else{}          ;                                    //      RET     NZ
                    ;        ;IY = 0xBA30             ;                                  ;                             //      LD      IY,BA30h
                    ;        ;DE = 0x0004             ;                                  ;                             //      LD      DE,0004h
                    ;        ;H = 0x14              ;                                  ;                             //      LD      H,14h
                    ;        ;A = 0x00              ;                                  ;                             //      LD      A,00h
                    ;        ;GOS(*(sp++) = (int)&&C636;goto RMC426;C636:a=a;)               ;                             //      CALL    RMC426
a = A - H           ;f=a     ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;                             //      CP      H
                    ;        ;if (  F.Z ) {RET(goto **(--sp););}else{}          ;                                    //      RET     Z
                    ;        ;C = MEM[IX+0x00]      ;                                  ;                             //      LD      C,(IX+00h)
                    ;        ;B = MEM[IX+0x01]      ;                                  ;                             //      LD      B,(IX+01h)
                    ;        ;A = RMB610[0]             ;                                  ;                             //      LD      A,(RMB610)
a = A - C           ;f=a     ;A = a                 ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;                             //      SUB     C
                    ;        ;E = A                 ;                                  ;                             //      LD      E,A
                    ;        ;A = RMB611[0]             ;                                  ;                             //      LD      A,(RMB611)
a = A - B           ;f=a     ;A = a                 ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;                             //      SUB     B
                    ;        ;D = A                 ;                                  ;                             //      LD      D,A
a = A - 0x80        ;f=a     ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;                             //      CP      80h
                    ;        ;if (  F.C ) {goto RMC651;}else{}               ;                                   //      JR      C,RMC651
a = A               ;f=a     ;A = -a                ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;                             //      NEG
RMC651:                             //RMC651:
                    ;        ;H = A                 ;                                  ;                             //      LD      H,A
a = C + 1           ;f=a&0xff;C = a                 ;F.Z=((a&0xff)==0)  ;              ;                             //      INC     C
                    ;        ;A = E                 ;                                  ;                             //      LD      A,E
a = A - 0x80        ;f=a     ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;                             //      CP      80h
                    ;        ;if (  F.C ) {goto RMC65B;}else{}               ;                                   //      JR      C,RMC65B
a = A               ;f=a     ;A = -a                ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;                             //      NEG
a = C - 1           ;f=a&0xff;C = a                 ;F.Z=((a&0xff)==0)  ;              ;                             //      DEC     C
RMC65B:                             //RMC65B:
a = A - H           ;f=a     ;A = a                 ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;                             //      SUB     H
                    ;        ;H = A                 ;                                  ;                             //      LD      H,A
a = rand()          ;f=a&0xff;A = a                 ;F.Z=((a&0xff)==0)  ;              ;                             //      LD      A,R
a = A & 0x08        ;f=a&0xff;A = a                 ;F.Z=((a&0xff)==0)  ;F.C=0         ;                             //      AND     08h
                    ;        ;if (  F.Z ) {goto RMC686;}else{}               ;                                   //      JR      Z,RMC686
                    ;        ;A = H                 ;                                  ;                             //      LD      A,H
a = A - 0x80        ;f=a     ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;                             //      CP      80h
                    ;        ;if ( !F.C ) {goto RMC677;}else{}               ;                                   //      JR      NC,RMC677
                    ;        ;A = E                 ;                                  ;                             //      LD      A,E
a = A - 0x80        ;f=a     ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;                             //      CP      80h
                    ;        ;if ( !F.C ) {goto RMC672;}else{}               ;                                   //      JR      NC,RMC672
                    ;        ;L = 0x12              ;                                  ;                             //      LD      L,12h
a = C + 1           ;f=a&0xff;C = a                 ;F.Z=((a&0xff)==0)  ;              ;                             //      INC     C
                    ;        ;goto RMC69F               ;                                  ;                             //      JR      RMC69F
RMC672:                             //RMC672:
                    ;        ;L = 0x02              ;                                  ;                             //      LD      L,02h
a = C - 1           ;f=a&0xff;C = a                 ;F.Z=((a&0xff)==0)  ;              ;                             //      DEC     C
                    ;        ;goto RMC69F               ;                                  ;                             //      JR      RMC69F
RMC677:                             //RMC677:
                    ;        ;A = D                 ;                                  ;                             //      LD      A,D
a = A - 0x80        ;f=a     ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;                             //      CP      80h
                    ;        ;if ( !F.C ) {goto RMC681;}else{}               ;                                   //      JR      NC,RMC681
                    ;        ;L = 0x04              ;                                  ;                             //      LD      L,04h
a = B + 1           ;f=a&0xff;B = a                 ;F.Z=((a&0xff)==0)  ;              ;                             //      INC     B
                    ;        ;goto RMC69F               ;                                  ;                             //      JR      RMC69F
RMC681:                             //RMC681:
                    ;        ;L = 0x14              ;                                  ;                             //      LD      L,14h
a = B - 1           ;f=a&0xff;B = a                 ;F.Z=((a&0xff)==0)  ;              ;                             //      DEC     B
                    ;        ;goto RMC69F               ;                                  ;                             //      JR      RMC69F
RMC686:                             //RMC686:
                    ;        ;A = D                 ;                                  ;                             //      LD      A,D
a = A - 0x80        ;f=a     ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;                             //      CP      80h
                    ;        ;if ( !F.C ) {goto RMC690;}else{}               ;                                   //      JR      NC,RMC690
a = B + 1           ;f=a&0xff;B = a                 ;F.Z=((a&0xff)==0)  ;              ;                             //      INC     B
                    ;        ;L = 0x03              ;                                  ;                             //      LD      L,03h
                    ;        ;goto RMC693               ;                                  ;                             //      JR      RMC693
RMC690:                             //RMC690:
a = B - 1           ;f=a&0xff;B = a                 ;F.Z=((a&0xff)==0)  ;              ;                             //      DEC     B
                    ;        ;L = 0x01              ;                                  ;                             //      LD      L,01h
RMC693:                             //RMC693:
                    ;        ;A = E                 ;                                  ;                             //      LD      A,E
a = A - 0x80        ;f=a     ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;                             //      CP      80h
a = C - 1           ;f=a&0xff;C = a                 ;F.Z=((a&0xff)==0)  ;              ;                             //      DEC     C
                    ;        ;if ( !F.C ) {goto RMC69F;}else{}               ;                                   //      JR      NC,RMC69F
a = C + 1           ;f=a&0xff;C = a                 ;F.Z=((a&0xff)==0)  ;              ;                             //      INC     C
a = C + 1           ;f=a&0xff;C = a                 ;F.Z=((a&0xff)==0)  ;              ;                             //      INC     C
                    ;        ;A = 0x10              ;                                  ;                             //      LD      A,10h
a = A + L           ;f=a&0xff;A = a                 ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;                             //      ADD     L
                    ;        ;L = A                 ;                                  ;                             //      LD      L,A
RMC69F:                             //RMC69F:
a = IO[BC]          ;f=a&0xff;A = a                 ;F.Z=((a&0xff)==0)  ;              ;                             //      !IN      A,(C)
a = A - 0x10        ;f=a     ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;                             //      CP      10h
                    ;        ;if ( !F.C ) {RET(goto **(--sp););}else{}          ;                                    //      RET     NC
                    ;        ;MEM[IY+0x00] = C      ;                                  ;                             //      LD      (IY+00h),C
                    ;        ;MEM[IY+0x01] = B      ;                                  ;                             //      LD      (IY+01h),B
                    ;        ;MEM[IY+0x02] = L      ;                                  ;                             //      LD      (IY+02h),L
                    ;        ;MEM[IY+0x03] = 0x20   ;                                  ;                             //      LD      (IY+03h),20h
                    ;        ;A = 0x88              ;                                  ;                             //      LD      A,88h
a = A + L           ;f=a&0xff;A = a                 ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;                             //      ADD     L
                    ;        ;IO[BC] = A            ;                                  ;                             //      !OUT     (C),A
                    ;        ;RET(goto **(--sp);)         ;                                  ;                             //      RET
                    ;        ;a=a                   ;                                  ;                             //      NOP
RMC6B8:                             //RMC6B8:
                    ;        ;IX = 0xBB00             ;                                  ;                             //      LD      IX,BB00h
                    ;        ;DE = 0x0004             ;                                  ;                             //      LD      DE,0004h
                    ;        ;H = 0xFF              ;                                  ;                             //      LD      H,FFh
RMC6C1:                             //RMC6C1:
                    ;        ;A = MEM[IX+0x03]      ;                                  ;                             //      LD      A,(IX+03h)
a = A - 0x00        ;f=a     ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;                             //      CP      00h
                    ;        ;if (  F.Z ) {goto RMC6E2;}else{}               ;                                   //      JR      Z,RMC6E2
a = MEM[IX+0x03] - 1;f=a&0xff;MEM[IX+0x03] = a      ;F.Z=((a&0xff)==0)  ;              ;                             //      DEC     (IX+03h)
                    ;        ;if ( !F.Z ) {goto RMC6E2;}else{}               ;                                   //      JR      NZ,RMC6E2
                    ;        ;B = MEM[IX+0x01]      ;                                  ;                             //      LD      B,(IX+01h)
                    ;        ;MEM[IX+0x01] = 0x00   ;                                  ;                             //      LD      (IX+01h),00h
                    ;        ;C = MEM[IX+0x00]      ;                                  ;                             //      LD      C,(IX+00h)
a = IO[BC]          ;f=a&0xff;A = a                 ;F.Z=((a&0xff)==0)  ;              ;                             //      !IN      A,(C)
a = A - MEM[IX+0x02];f=a     ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;                             //      CP      (IX+02h)
                    ;        ;if ( !F.Z ) {goto RMC6E2;}else{}               ;                                   //      JR      NZ,RMC6E2
                    ;        ;A = 0x00              ;                                  ;                             //      LD      A,00h
                    ;        ;IO[BC] = A            ;                                  ;                             //      !OUT     (C),A
RMC6E2:                             //RMC6E2:
a = IX + DE         ;f=a     ;IX = a                ;                   ;F.C=a>>16     ;                             //      ADD     IX,DE
a = H - 1           ;f=a&0xff;H = a                 ;F.Z=((a&0xff)==0)  ;              ;                             //      DEC     H
                    ;        ;if ( !F.Z ) {goto RMC6C1;}else{}               ;                                   //      JR      NZ,RMC6C1
                    ;        ;RET(goto **(--sp);)         ;                                  ;                             //      RET
RMC6E8:                             //RMC6E8:
                    ;        ;IX = 0xB610             ;                                  ;                             //      LD      IX,B610h
                    ;        ;A = MEM[IX+0x05]      ;                                  ;                             //      LD      A,(IX+05h)
a = A - 0x00        ;f=a     ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;                             //      CP      00h
                    ;        ;if (  F.Z ) {RET(goto **(--sp););}else{}          ;                                    //      RET     Z
                    ;        ;A = MEM[IX+0x04]      ;                                  ;                             //      LD      A,(IX+04h)
a = A & 0x7F        ;f=a&0xff;A = a                 ;F.Z=((a&0xff)==0)  ;F.C=0         ;                             //      AND     7Fh
a = A - 0x02        ;f=a     ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;                             //      CP      02h
                    ;        ;if ( !F.C ) {RET(goto **(--sp););}else{}          ;                                    //      RET     NC
                    ;        ;IY = 0xBA00             ;                                  ;                             //      LD      IY,BA00h
                    ;        ;DE = 0x0004             ;                                  ;                             //      LD      DE,0004h
                    ;        ;H = 0x04              ;                                  ;                             //      LD      H,04h
                    ;        ;A = 0x00              ;                                  ;                             //      LD      A,00h
                    ;        ;GOS(*(sp++) = (int)&&C705;goto RMC426;C705:a=a;)               ;                             //      CALL    RMC426
                    ;        ;*(SP++)=IY            ;                                  ;                             //      PUSH    IY
                    ;        ;HL=*(--SP)            ;                                  ;                             //      POP     HL
                    ;        ;A = L                 ;                                  ;                             //      LD      A,L
a = A - 0x10        ;f=a     ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;                             //      CP      10h
                    ;        ;if (  F.Z ) {RET(goto **(--sp););}else{}          ;                                    //      RET     Z
                    ;        ;A = 0x00              ;                                  ;                             //      LD      A,00h
                    ;        ;GOS(*(sp++) = (int)&&C711;goto RM001B;C711:a=a;)               ;                             //      CALL    RM001B
                    ;        ;C = RMB610[0];B = RMB610[1]   ;                                  ;                             //      LD      BC,(RMB610)
a = A - 0x37        ;f=a     ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;                             //      CP      37h
                    ;        ;if ( !F.Z ) {goto RMC71D;}else{}               ;                                   //      JR      NZ,RMC71D
a = C + 1           ;f=a&0xff;C = a                 ;F.Z=((a&0xff)==0)  ;              ;                             //      INC     C
RMC71D:                             //RMC71D:
                    ;        ;E = 0x01              ;                                  ;                             //      LD      E,01h
                    ;        ;D = 0x40              ;                                  ;                             //      LD      D,40h
a = A - 0x31        ;f=a     ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;                             //      CP      31h
                    ;        ;if (  F.Z ) {goto RMC72E;}else{}               ;                                   //      JR      Z,RMC72E
a = A - 0x34        ;f=a     ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;                             //      CP      34h
                    ;        ;if (  F.Z ) {goto RMC730;}else{}               ;                                   //      JR      Z,RMC730
a = A - 0x37        ;f=a     ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;                             //      CP      37h
                    ;        ;if (  F.Z ) {goto RMC732;}else{}               ;                                   //      JR      Z,RMC732
                    ;        ;RET(goto **(--sp);)         ;                                  ;                             //      RET
RMC72E:                             //RMC72E:
a = E + 1           ;f=a&0xff;E = a                 ;F.Z=((a&0xff)==0)  ;              ;                             //      INC     E
a = D + 1           ;f=a&0xff;D = a                 ;F.Z=((a&0xff)==0)  ;              ;                             //      INC     D
RMC730:                             //RMC730:
a = E + 1           ;f=a&0xff;E = a                 ;F.Z=((a&0xff)==0)  ;              ;                             //      INC     E
a = D + 1           ;f=a&0xff;D = a                 ;F.Z=((a&0xff)==0)  ;              ;                             //      INC     D
RMC732:                             //RMC732:
                    ;        ;A = MEM[IX+0x04]      ;                                  ;                             //      LD      A,(IX+04h)
a = A - 0x80        ;f=a     ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;                             //      CP      80h
                    ;        ;if (  F.Z ) {goto RMC759;}else{}               ;                                   //      JR      Z,RMC759
                    ;        ;MEM[IY+0x00] = C      ;                                  ;                             //      LD      (IY+00h),C
                    ;        ;MEM[IY+0x01] = B      ;                                  ;                             //      LD      (IY+01h),B
                    ;        ;MEM[IY+0x02] = E      ;                                  ;                             //      LD      (IY+02h),E
                    ;        ;MEM[IY+0x03] = 0x10   ;                                  ;                             //      LD      (IY+03h),10h
                    ;        ;MEM[IX+0x07] = D      ;                                  ;                             //      LD      (IX+07h),D
                    ;        ;C = RMB610[0];B = RMB610[1]   ;                                  ;                             //      LD      BC,(RMB610)
                    ;        ;IO[BC] = D            ;                                  ;                             //      !OUT     (C),D
a = C + 1           ;f=a&0xff;C = a                 ;F.Z=((a&0xff)==0)  ;              ;                             //      INC     C
                    ;        ;A = D                 ;                                  ;                             //      LD      A,D
a = A + 0x10        ;f=a&0xff;A = a                 ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;                             //      ADD     10h
                    ;        ;IO[BC] = A            ;                                  ;                             //      !OUT     (C),A
a = MEM[IX+0x05] - 1;f=a&0xff;MEM[IX+0x05] = a      ;F.Z=((a&0xff)==0)  ;              ;                             //      DEC     (IX+05h)
                    ;        ;RET(goto **(--sp);)         ;                                  ;                             //      RET
RMC759:                             //RMC759:
                    ;        ;C = RMB602[0];B = RMB602[1]   ;                                  ;                             //      LD      BC,(RMB602)
                    ;        ;MEM[IY+0x00] = C      ;                                  ;                             //      LD      (IY+00h),C
                    ;        ;MEM[IY+0x01] = B      ;                                  ;                             //      LD      (IY+01h),B
                    ;        ;MEM[IY+0x02] = E      ;                                  ;                             //      LD      (IY+02h),E
                    ;        ;MEM[IY+0x03] = 0x03   ;                                  ;                             //      LD      (IY+03h),03h
                    ;        ;RET(goto **(--sp);)         ;                                  ;                             //      RET


RMC76B:                             //RMC76B:
                    ;        ;IX = 0xBA00             ;                                  ;                             //      LD      IX,BA00h
                    ;        ;B = 0x0C              ;                                  ;                             //      LD      B,0Ch
RMC771:                             //RMC771:
                    ;        ;*(SP++)=BC            ;                                  ;                             //      PUSH    BC
                    ;        ;A = MEM[IX+0x01]      ;                                  ;                             //      LD      A,(IX+01h)
a = A - 0x00        ;f=a     ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;                             //      CP      00h
                    ;        ;if (  F.Z ) {goto RMC77E;}else{}               ;                                   //      JR      Z,RMC77E
                    ;        ;L = 0xFF              ;                                  ;                             //      LD      L,FFh
                    ;        ;GOS(*(sp++) = (int)&&C77B;goto RMC7A4;C77B:a=a;)               ;                             //      CALL    RMC7A4
RMC77E:                             //RMC77E:
                    ;        ;BC=*(--SP)            ;                                  ;                             //      POP     BC
                    ;        ;IX++                  ;                                  ;                             //      INC     IX
                    ;        ;IX++                  ;                                  ;                             //      INC     IX
                    ;        ;IX++                  ;                                  ;                             //      INC     IX
                    ;        ;IX++                  ;                                  ;                             //      INC     IX
                    ;        ;if ( --B > 0 ) {goto RMC771;}else{}             ;                                    //      DJNZ    RMC771
                    ;        ;B = 0x14              ;                                  ;                             //      LD      B,14h
RMC78B:                             //RMC78B:
                    ;        ;*(SP++)=BC            ;                                  ;                             //      PUSH    BC
                    ;        ;A = MEM[IX+0x01]      ;                                  ;                             //      LD      A,(IX+01h)
a = A - 0x00        ;f=a     ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;                             //      CP      00h
                    ;        ;if (  F.Z ) {goto RMC798;}else{}               ;                                   //      JR      Z,RMC798
                    ;        ;L = 0x01              ;                                  ;                             //      LD      L,01h
                    ;        ;GOS(*(sp++) = (int)&&C795;goto RMC7A4;C795:a=a;)               ;                             //      CALL    RMC7A4
RMC798:                             //RMC798:
                    ;        ;BC=*(--SP)            ;                                  ;                             //      POP     BC
                    ;        ;IX++                  ;                                  ;                             //      INC     IX
                    ;        ;IX++                  ;                                  ;                             //      INC     IX
                    ;        ;IX++                  ;                                  ;                             //      INC     IX
                    ;        ;IX++                  ;                                  ;                             //      INC     IX
                    ;        ;if ( --B > 0 ) {goto RMC78B;}else{}             ;                                    //      DJNZ    RMC78B
                    ;        ;RET(goto **(--sp);)         ;                                  ;                             //      RET


RMC7A4:                             //RMC7A4:
                    ;        ;C = MEM[IX+0x00]      ;                                  ;                             //      LD      C,(IX+00h)
                    ;        ;B = MEM[IX+0x01]      ;                                  ;                             //      LD      B,(IX+01h)
a = IO[BC]          ;f=a&0xff;A = a                 ;F.Z=((a&0xff)==0)  ;              ;                             //      !IN      A,(C)
a = A - 0x10        ;f=a     ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;                             //      CP      10h
                    ;        ;if (  F.C ) {goto RMC7B7;}else{}               ;                                   //      JR      C,RMC7B7
a = A - 0x30        ;f=a     ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;                             //      CP      30h
                    ;        ;if (  F.C ) {goto RMC7EC;}else{}               ;                                   //      JR      C,RMC7EC
        ;if ( !F.C ) {GOS(*(sp++) = (int)&&C7B4;goto RMC831;C7B4:a=a;);};                                   //      CALL    NC,RMC831
RMC7B7:                             //RMC7B7:
                    ;        ;D = A                 ;                                  ;                             //      LD      D,A
                    ;        ;A = MEM[IX+0x02]      ;                                  ;                             //      LD      A,(IX+02h)
a = A & (1<<2)     ;f=a&0xff;                      ;F.Z=((a&0xff)==0)  ;              ;                             //      BIT     2,A
                    ;        ;if (  F.Z ) {goto RMC7C3;}else{}               ;                                   //      JR      Z,RMC7C3
                    ;        ;A = 0x11              ;                                  ;                             //      LD      A,11h
                    ;        ;goto RMC7CD               ;                                  ;                             //      JR      RMC7CD
RMC7C3:                             //RMC7C3:
a = A - 0x10        ;f=a     ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;                             //      CP      10h
                    ;        ;if (  F.C ) {goto RMC7CB;}else{}               ;                                   //      JR      C,RMC7CB
a = A               ;f=a     ;A = -a                ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;                             //      NEG
a = A + 0x14        ;f=a&0xff;A = a                 ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;                             //      ADD     14h
RMC7CB:                             //RMC7CB:
a = A + 0x20        ;f=a&0xff;A = a                 ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;                             //      ADD     20h
RMC7CD:                             //RMC7CD:
                    ;        ;IO[BC] = A            ;                                  ;                             //      !OUT     (C),A
                    ;        ;*(SP++)=AF            ;                                  ;                             //      PUSH    AF
                    ;        ;IY = 0xBB00             ;                                  ;                             //      LD      IY,BB00h
                    ;        ;DE = 0x0004             ;                                  ;                             //      LD      DE,0004h
                    ;        ;H = 0xFF              ;                                  ;                             //      LD      H,FFh
                    ;        ;A = 0x00              ;                                  ;                             //      LD      A,00h
                    ;        ;GOS(*(sp++) = (int)&&C7DB;goto RMC426;C7DB:a=a;)               ;                             //      CALL    RMC426
                    ;        ;AF=*(--SP)            ;                                  ;                             //      POP     AF
                    ;        ;MEM[IY+0x00] = C      ;                                  ;                             //      LD      (IY+00h),C
                    ;        ;MEM[IY+0x01] = B      ;                                  ;                             //      LD      (IY+01h),B
                    ;        ;MEM[IY+0x02] = A      ;                                  ;                             //      LD      (IY+02h),A
                    ;        ;MEM[IY+0x03] = 0x08   ;                                  ;                             //      LD      (IY+03h),08h
RMC7EC:                             //RMC7EC:
a = MEM[IX+0x03] - 1;f=a&0xff;MEM[IX+0x03] = a      ;F.Z=((a&0xff)==0)  ;              ;                             //      DEC     (IX+03h)
        ;if (  F.Z ) {GOS(*(sp++) = (int)&&C7EF;goto RMC837;C7EF:a=a;);};                                   //      CALL    Z,RMC837
                    ;        ;A = MEM[IX+0x02]      ;                                  ;                             //      LD      A,(IX+02h)
a = A - 0x14        ;f=a     ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;                             //      CP      14h
                    ;        ;if ( !F.Z ) {goto RMC7FC;}else{}               ;                                   //      JR      NZ,RMC7FC
a = B - 1           ;f=a&0xff;B = a                 ;F.Z=((a&0xff)==0)  ;              ;                             //      DEC     B
                    ;        ;goto RMC810               ;                                  ;                             //      JR      RMC810
RMC7FC:                             //RMC7FC:
a = A - 0x04        ;f=a     ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;                             //      CP      04h
                    ;        ;if ( !F.Z ) {goto RMC803;}else{}               ;                                   //      JR      NZ,RMC803
a = B + 1           ;f=a&0xff;B = a                 ;F.Z=((a&0xff)==0)  ;              ;                             //      INC     B
                    ;        ;goto RMC810               ;                                  ;                             //      JR      RMC810
RMC803:                             //RMC803:
a = A - 0x10        ;f=a     ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;                             //      CP      10h
                    ;        ;if (  F.C ) {goto RMC809;}else{}               ;                                   //      JR      C,RMC809
a = C + 1           ;f=a&0xff;C = a                 ;F.Z=((a&0xff)==0)  ;              ;                             //      INC     C
a = C + 1           ;f=a&0xff;C = a                 ;F.Z=((a&0xff)==0)  ;              ;                             //      INC     C
RMC809:                             //RMC809:
a = C - 1           ;f=a&0xff;C = a                 ;F.Z=((a&0xff)==0)  ;              ;                             //      DEC     C
a = A & 0x0F        ;f=a&0xff;A = a                 ;F.Z=((a&0xff)==0)  ;F.C=0         ;                             //      AND     0Fh
a = A - 0x02        ;f=a     ;A = a                 ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;                             //      SUB     02h
a = A + B           ;f=a&0xff;A = a                 ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;                             //      ADD     B
                    ;        ;B = A                 ;                                  ;                             //      LD      B,A
RMC810:                             //RMC810:
a = IO[BC]          ;f=a&0xff;A = a                 ;F.Z=((a&0xff)==0)  ;              ;                             //      !IN      A,(C)
a = A - 0x10        ;f=a     ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;                             //      CP      10h
                    ;        ;if (  F.C ) {goto RMC81D;}else{}               ;                                   //      JR      C,RMC81D
a = A - 0x30        ;f=a     ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;                             //      CP      30h
                    ;        ;if (  F.C ) {goto RMC829;}else{}               ;                                   //      JR      C,RMC829
        ;if ( !F.C ) {GOS(*(sp++) = (int)&&C81A;goto RMC831;C81A:a=a;);};                                   //      CALL    NC,RMC831
RMC81D:                             //RMC81D:
                    ;        ;A = MEM[IX+0x02]      ;                                  ;                             //      LD      A,(IX+02h)
a = A + 0x48        ;f=a&0xff;A = a                 ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;                             //      ADD     48h
a = L - 1           ;f=a&0xff;L = a                 ;F.Z=((a&0xff)==0)  ;              ;                             //      DEC     L
                    ;        ;if ( !F.Z ) {goto RMC827;}else{}               ;                                   //      JR      NZ,RMC827
a = A + 0x40        ;f=a&0xff;A = a                 ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;                             //      ADD     40h
RMC827:                             //RMC827:
                    ;        ;IO[BC] = A            ;                                  ;                             //      !OUT     (C),A
RMC829:                             //RMC829:
                    ;        ;MEM[IX+0x00] = C      ;                                  ;                             //      LD      (IX+00h),C
                    ;        ;MEM[IX+0x01] = B      ;                                  ;                             //      LD      (IX+01h),B
                    ;        ;RET(goto **(--sp);)         ;                                  ;                             //      RET
                    ;        ;a=a                   ;                                  ;                             //      NOP

RMC831:                             //RMC831:
a = IO[BC]          ;f=a&0xff;A = a                 ;F.Z=((a&0xff)==0)  ;              ;                             //      !IN      A,(C)
a = A - 0xF0        ;f=a     ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;                             //      CP      F0h
                    ;        ;if (  F.C ) {goto RMC89C;}else{}               ;                                   //      JR      C,RMC89C

RMC837:                             //RMC837:
                    ;        ;C = MEM[IX+0x00]      ;                                  ;                             //      LD      C,(IX+00h)
                    ;        ;B = MEM[IX+0x01]      ;                                  ;                             //      LD      B,(IX+01h)
                    ;        ;A = MEM[IX+0x03]      ;                                  ;                             //      LD      A,(IX+03h)
a = A - 0x00        ;f=a     ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;                             //      CP      00h
                    ;        ;if (  F.Z ) {goto RMC863;}else{}               ;                                   //      JR      Z,RMC863
                    ;        ;A = MEM[IX+0x02]      ;                                  ;                             //      LD      A,(IX+02h)
a = A - 0x14        ;f=a     ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;                             //      CP      14h
                    ;        ;if ( !F.Z ) {goto RMC84F;}else{}               ;                                   //      JR      NZ,RMC84F
                    ;        ;A = 0x15              ;                                  ;                             //      LD      A,15h
                    ;        ;goto RMC865               ;                                  ;                             //      JR      RMC865
RMC84F:                             //RMC84F:
a = A - 0x04        ;f=a     ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;                             //      CP      04h
                    ;        ;if ( !F.Z ) {goto RMC857;}else{}               ;                                   //      JR      NZ,RMC857
                    ;        ;A = 0x14              ;                                  ;                             //      LD      A,14h
                    ;        ;goto RMC865               ;                                  ;                             //      JR      RMC865
RMC857:                             //RMC857:
a = A - 0x10        ;f=a     ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;                             //      CP      10h
                    ;        ;if ( !F.C ) {goto RMC85F;}else{}               ;                                   //      JR      NC,RMC85F
a = A + 0x23        ;f=a&0xff;A = a                 ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;                             //      ADD     23h
                    ;        ;goto RMC865               ;                                  ;                             //      JR      RMC865
RMC85F:                             //RMC85F:
a = A + 0x17        ;f=a&0xff;A = a                 ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;                             //      ADD     17h
                    ;        ;goto RMC865               ;                                  ;                             //      JR      RMC865
RMC863:                             //RMC863:
                    ;        ;A = 0x27              ;                                  ;                             //      LD      A,27h
RMC865:                             //RMC865:
                    ;        ;E = A                 ;                                  ;                             //      LD      E,A
a = IO[BC]          ;f=a&0xff;A = a                 ;F.Z=((a&0xff)==0)  ;              ;                             //      !IN      A,(C)
a = A - 0x40        ;f=a     ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;                             //      CP      40h
                    ;        ;if ( !F.C ) {goto RMC876;}else{}               ;                                   //      JR      NC,RMC876
a = A - 0x10        ;f=a     ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;                             //      CP      10h
                    ;        ;if (  F.C ) {goto RMC876;}else{}               ;                                   //      JR      C,RMC876
a = A & 0x0F        ;f=a&0xff;A = a                 ;F.Z=((a&0xff)==0)  ;F.C=0         ;                             //      AND     0Fh
a = A - 0x04        ;f=a     ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;                             //      CP      04h
                    ;        ;if ( !F.C ) {goto RMC896;}else{}               ;                                   //      JR      NC,RMC896
RMC876:                             //RMC876:
                    ;        ;IO[BC] = E            ;                                  ;                             //      !OUT     (C),E
                    ;        ;A = E                 ;                                  ;                             //      LD      A,E
                    ;        ;*(SP++)=AF            ;                                  ;                             //      PUSH    AF
                    ;        ;IY = 0xBB00             ;                                  ;                             //      LD      IY,BB00h
                    ;        ;DE = 0x0004             ;                                  ;                             //      LD      DE,0004h
                    ;        ;H = 0xFF              ;                                  ;                             //      LD      H,FFh
                    ;        ;A = 0x00              ;                                  ;                             //      LD      A,00h
                    ;        ;GOS(*(sp++) = (int)&&C885;goto RMC426;C885:a=a;)               ;                             //      CALL    RMC426
                    ;        ;AF=*(--SP)            ;                                  ;                             //      POP     AF
                    ;        ;MEM[IY+0x00] = C      ;                                  ;                             //      LD      (IY+00h),C
                    ;        ;MEM[IY+0x01] = B      ;                                  ;                             //      LD      (IY+01h),B
                    ;        ;MEM[IY+0x02] = A      ;                                  ;                             //      LD      (IY+02h),A
                    ;        ;MEM[IY+0x03] = 0x10   ;                                  ;                             //      LD      (IY+03h),10h
RMC896:                             //RMC896:
                    ;        ;MEM[IX+0x01] = 0x00   ;                                  ;                             //      LD      (IX+01h),00h
//      POP     DE                             ////      POP     DE
sp--;cnt_sp--;                             ////c:sp--;cnt_sp--;
                    ;        ;RET(goto **(--sp);)         ;                                  ;                             //      RET

RMC89C:                             //RMC89C:
a = A - 0x40        ;f=a     ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;                             //      CP      40h
        ;if (  F.C ) goto RMCA8E   ;                                  ;                                   //      JP      C,RMCA8E
a = A - 0xC0        ;f=a     ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;                             //      CP      C0h
        ;if ( !F.C ) goto RMC9F1   ;                                  ;                                   //      JP      NC,RMC9F1
                    ;        ;D = A                 ;                                  ;                             //      LD      D,A
a = A ^ L           ;f=a&0xff;A = a                 ;F.Z=((a&0xff)==0)  ;F.C=0         ;                             //      XOR     L
a = A - 0x80        ;f=a     ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;                             //      CP      80h
                    ;        ;A = D                 ;                                  ;                             //      LD      A,D
                    ;        ;if ( !F.C ) {RET(goto **(--sp););}else{}          ;                                    //      RET     NC
a = A & 0x0F        ;f=a&0xff;A = a                 ;F.Z=((a&0xff)==0)  ;F.C=0         ;                             //      AND     0Fh
a = A - 0x09        ;f=a     ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;                             //      CP      09h
                    ;        ;A = D                 ;                                  ;                             //      LD      A,D
        ;if ( !F.C ) goto RMC983   ;                                  ;                                   //      JP      NC,RMC983
                    ;        ;A = 0x20              ;                                  ;                             //      LD      A,20h
                    ;        ;RMB60F[0] = A             ;                                  ;                             //      LD      (RMB60F),A
                    ;        ;A = D                 ;                                  ;                             //      LD      A,D
a = A & 0x1F        ;f=a&0xff;A = a                 ;F.Z=((a&0xff)==0)  ;F.C=0         ;                             //      AND     1Fh
a = A - 0x10        ;f=a     ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;                             //      CP      10h
                    ;        ;if (  F.C ) {goto RMC8C1;}else{}               ;                                   //      JR      C,RMC8C1
a = C - 1           ;f=a&0xff;C = a                 ;F.Z=((a&0xff)==0)  ;              ;                             //      DEC     C
RMC8C1:                             //RMC8C1:
a = A & 0x0F        ;f=a&0xff;A = a                 ;F.Z=((a&0xff)==0)  ;F.C=0         ;                             //      AND     0Fh
a = A - 0x03        ;f=a     ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;                             //      CP      03h
                    ;        ;if (  F.C ) {goto RMC8C8;}else{}               ;                                   //      JR      C,RMC8C8
a = B - 1           ;f=a&0xff;B = a                 ;F.Z=((a&0xff)==0)  ;              ;                             //      DEC     B
RMC8C8:                             //RMC8C8:
                    ;        ;IY = 0xB610             ;                                  ;                             //      LD      IY,B610h
                    ;        ;DE = 0x0010             ;                                  ;                             //      LD      DE,0010h
                    ;        ;H = 0x3F              ;                                  ;                             //      LD      H,3Fh
RMC8D1:                             //RMC8D1:
                    ;        ;A = B                 ;                                  ;                             //      LD      A,B
                    ;        ;GOS(*(sp++) = (int)&&C8D2;goto RMC426;C8D2:a=a;)               ;                             //      CALL    RMC426
                    ;        ;A = MEM[IY+0x00]      ;                                  ;                             //      LD      A,(IY+00h)
a = IY + DE         ;f=a     ;IY = a                ;                   ;F.C=a>>16     ;                             //      ADD     IY,DE
a = H - 1           ;f=a&0xff;H = a                 ;F.Z=((a&0xff)==0)  ;              ;                             //      DEC     H
a = H + 1           ;f=a&0xff;H = a                 ;F.Z=((a&0xff)==0)  ;              ;                             //      INC     H
                    ;        ;if (  F.Z ) {RET(goto **(--sp););}else{}          ;                                    //      RET     Z
a = H - 1           ;f=a&0xff;H = a                 ;F.Z=((a&0xff)==0)  ;              ;                             //      DEC     H
                    ;        ;if (  F.Z ) {RET(goto **(--sp););}else{}          ;                                    //      RET     Z
a = A - C           ;f=a     ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;                             //      CP      C
                    ;        ;if ( !F.Z ) {goto RMC8D1;}else{}               ;                                   //      JR      NZ,RMC8D1
                    ;        ;DE = 0xFFF0             ;                                  ;                             //      LD      DE,FFF0h
a = IY + DE         ;f=a     ;IY = a                ;                   ;F.C=a>>16     ;                             //      ADD     IY,DE
a = MEM[IY+0x09] - 1;f=a&0xff;MEM[IY+0x09] = a      ;F.Z=((a&0xff)==0)  ;              ;                             //      DEC     (IY+09h)
                    ;        ;if ( !F.Z ) {goto RMC93B;}else{}               ;                                   //      JR      NZ,RMC93B
                    ;        ;MEM[IY+0x01] = 0x00   ;                                  ;                             //      LD      (IY+01h),00h
                    ;        ;MEM[IX+0x01] = 0x00   ;                                  ;                             //      LD      (IX+01h),00h
                    ;        ;IY = 0xBB00             ;                                  ;                             //      LD      IY,BB00h
                    ;        ;DE = 0x0004             ;                                  ;                             //      LD      DE,0004h
                    ;        ;H = 0xFF              ;                                  ;                             //      LD      H,FFh
                    ;        ;A = 0x2A              ;                                  ;                             //      LD      A,2Ah
                    ;        ;IO[BC] = A            ;                                  ;                             //      !OUT     (C),A
                    ;        ;GOS(*(sp++) = (int)&&C901;goto RMC926;C901:a=a;)               ;                             //      CALL    RMC926
                    ;        ;A = 0x26              ;                                  ;                             //      LD      A,26h
a = C + 1           ;f=a&0xff;C = a                 ;F.Z=((a&0xff)==0)  ;              ;                             //      INC     C
                    ;        ;IO[BC] = A            ;                                  ;                             //      !OUT     (C),A
                    ;        ;GOS(*(sp++) = (int)&&C909;goto RMC926;C909:a=a;)               ;                             //      CALL    RMC926
                    ;        ;A = 0x24              ;                                  ;                             //      LD      A,24h
a = B + 1           ;f=a&0xff;B = a                 ;F.Z=((a&0xff)==0)  ;              ;                             //      INC     B
                    ;        ;IO[BC] = A            ;                                  ;                             //      !OUT     (C),A
                    ;        ;GOS(*(sp++) = (int)&&C911;goto RMC926;C911:a=a;)               ;                             //      CALL    RMC926
                    ;        ;A = 0x28              ;                                  ;                             //      LD      A,28h
a = C - 1           ;f=a&0xff;C = a                 ;F.Z=((a&0xff)==0)  ;              ;                             //      DEC     C
                    ;        ;IO[BC] = A            ;                                  ;                             //      !OUT     (C),A
                    ;        ;GOS(*(sp++) = (int)&&C919;goto RMC926;C919:a=a;)               ;                             //      CALL    RMC926
//      POP     AF                             ////      POP     AF
sp--;cnt_sp--;                             ////c:sp--;cnt_sp--;
                    ;        ;A = L                 ;                                  ;                             //      LD      A,L
a = A - 1           ;f=a&0xff;A = a                 ;F.Z=((a&0xff)==0)  ;              ;                             //      DEC     A
                    ;        ;if (  F.Z ) {goto RMC926;}else{}               ;                                   //      JR      Z,RMC926
                    ;        ;A = 0x30              ;                                  ;                             //      LD      A,30h
                    ;        ;GOS(*(sp++) = (int)&&C923;goto RMCBCD;C923:a=a;)               ;                             //      CALL    RMCBCD
RMC926:                             //RMC926:
                    ;        ;*(SP++)=AF            ;                                  ;                             //      PUSH    AF
                    ;        ;A = 0x00              ;                                  ;                             //      LD      A,00h
                    ;        ;GOS(*(sp++) = (int)&&C929;goto RMC426;C929:a=a;)               ;                             //      CALL    RMC426
                    ;        ;AF=*(--SP)            ;                                  ;                             //      POP     AF
                    ;        ;MEM[IY+0x00] = C      ;                                  ;                             //      LD      (IY+00h),C
                    ;        ;MEM[IY+0x01] = B      ;                                  ;                             //      LD      (IY+01h),B
                    ;        ;MEM[IY+0x02] = A      ;                                  ;                             //      LD      (IY+02h),A
                    ;        ;MEM[IY+0x03] = 0x20   ;                                  ;                             //      LD      (IY+03h),20h
                    ;        ;RET(goto **(--sp);)         ;                                  ;                             //      RET
RMC93B:                             //RMC93B:
                    ;        ;A = MEM[IX+0x02]      ;                                  ;                             //      LD      A,(IX+02h)
                    ;        ;E = 0x01              ;                                  ;                             //      LD      E,01h
a = A & (1<<3)     ;f=a&0xff;                      ;F.Z=((a&0xff)==0)  ;              ;                             //      BIT     3,A
                    ;        ;if ( !F.Z ) {goto RMC949;}else{}               ;                                   //      JR      NZ,RMC949
a = A - 0x10        ;f=a     ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;                             //      CP      10h
                    ;        ;if ( !F.C ) {goto RMC94A;}else{}               ;                                   //      JR      NC,RMC94A
a = E - 1           ;f=a&0xff;E = a                 ;F.Z=((a&0xff)==0)  ;              ;                             //      DEC     E
RMC949:                             //RMC949:
a = E - 1           ;f=a&0xff;E = a                 ;F.Z=((a&0xff)==0)  ;              ;                             //      DEC     E
RMC94A:                             //RMC94A:
                    ;        ;MEM[IY+0x02] = E      ;                                  ;                             //      LD      (IY+02h),E
a = A - 0x14        ;f=a     ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;                             //      CP      14h
                    ;        ;if (  F.Z ) {goto RMC95F;}else{}               ;                                   //      JR      Z,RMC95F
a = A - 0x04        ;f=a     ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;                             //      CP      04h
                    ;        ;if (  F.Z ) {goto RMC963;}else{}               ;                                   //      JR      Z,RMC963
a = A & 0x0F        ;f=a&0xff;A = a                 ;F.Z=((a&0xff)==0)  ;F.C=0         ;                             //      AND     0Fh
a = A - 0x02        ;f=a     ;A = a                 ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;                             //      SUB     02h
a = A<<1            ;f=a&0xff;A = a                 ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;                             //      SLA     A
a = A<<1            ;f=a&0xff;A = a                 ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;                             //      SLA     A
                    ;        ;goto RMC965               ;                                  ;                             //      JR      RMC965
RMC95F:                             //RMC95F:
                    ;        ;A = 0xFC              ;                                  ;                             //      LD      A,FCh
                    ;        ;goto RMC965               ;                                  ;                             //      JR      RMC965
RMC963:                             //RMC963:
                    ;        ;A = 0x04              ;                                  ;                             //      LD      A,04h
RMC965:                             //RMC965:
                    ;        ;MEM[IY+0x03] = A      ;                                  ;                             //      LD      (IY+03h),A
                    ;        ;*(SP++)=BC            ;                                  ;                             //      PUSH    BC
                    ;        ;*(SP++)=HL            ;                                  ;                             //      PUSH    HL
                    ;        ;*(SP++)=IX            ;                                  ;                             //      PUSH    IX
                    ;        ;*(SP++)=IY            ;                                  ;                             //      PUSH    IY
                    ;        ;IX=*(--SP)            ;                                  ;                             //      POP     IX
                    ;        ;GOS(*(sp++) = (int)&&C970;goto RMC00D;C970:a=a;)               ;                             //      CALL    RMC00D
                    ;        ;IX=*(--SP)            ;                                  ;                             //      POP     IX
                    ;        ;HL=*(--SP)            ;                                  ;                             //      POP     HL
                    ;        ;BC=*(--SP)            ;                                  ;                             //      POP     BC
                    ;        ;A = L                 ;                                  ;                             //      LD      A,L
a = A - 1           ;f=a&0xff;A = a                 ;F.Z=((a&0xff)==0)  ;              ;                             //      DEC     A
                    ;        ;if (  F.Z ) {goto RMC980;}else{}               ;                                   //      JR      Z,RMC980
                    ;        ;A = 0x03              ;                                  ;                             //      LD      A,03h
                    ;        ;GOS(*(sp++) = (int)&&C97D;goto RMCBCD;C97D:a=a;)               ;                             //      CALL    RMCBCD
RMC980:                             //RMC980:
                    ;        ;goto RMC837               ;                                  ;                             //      JP      RMC837
RMC983:                             //RMC983:
a = A & 0xF0        ;f=a&0xff;A = a                 ;F.Z=((a&0xff)==0)  ;F.C=0         ;                             //      AND     F0h
a = A - 0x40        ;f=a     ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;                             //      CP      40h
                    ;        ;if (  F.Z ) {goto RMC992;}else{}               ;                                   //      JR      Z,RMC992
a = A - 0x80        ;f=a     ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;                             //      CP      80h
                    ;        ;if (  F.Z ) {goto RMC992;}else{}               ;                                   //      JR      Z,RMC992
a = A - 0x90        ;f=a     ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;                             //      CP      90h
                    ;        ;A = D                 ;                                  ;                             //      LD      A,D
                    ;        ;if ( !F.Z ) {goto RMC9C9;}else{}               ;                                   //      JR      NZ,RMC9C9
RMC992:                             //RMC992:
                    ;        ;IY = 0xBA00             ;                                  ;                             //      LD      IY,BA00h
                    ;        ;H = 0x20              ;                                  ;                             //      LD      H,20h
                    ;        ;DE = 0x0004             ;                                  ;                             //      LD      DE,0004h
RMC99B:                             //RMC99B:
                    ;        ;A = B                 ;                                  ;                             //      LD      A,B
                    ;        ;GOS(*(sp++) = (int)&&C99C;goto RMC426;C99C:a=a;)               ;                             //      CALL    RMC426
                    ;        ;A = C                 ;                                  ;                             //      LD      A,C
a = A - MEM[IY+0x00];f=a     ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;                             //      CP      (IY+00h)
                    ;        ;if (  F.Z ) {goto RMC9AF;}else{}               ;                                   //      JR      Z,RMC9AF
                    ;        ;A = H                 ;                                  ;                             //      LD      A,H
a = A - 0x00        ;f=a     ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;                             //      CP      00h
                    ;        ;if (  F.Z ) {RET(goto **(--sp););}else{}          ;                                    //      RET     Z
a = H - 1           ;f=a&0xff;H = a                 ;F.Z=((a&0xff)==0)  ;              ;                             //      DEC     H
                    ;        ;if (  F.Z ) {RET(goto **(--sp););}else{}          ;                                    //      RET     Z
a = IY + DE         ;f=a     ;IY = a                ;                   ;F.C=a>>16     ;                             //      ADD     IY,DE
                    ;        ;goto RMC99B               ;                                  ;                             //      JR      RMC99B
RMC9AF:                             //RMC9AF:
                    ;        ;MEM[IX+0x01] = 0x00   ;                                  ;                             //      LD      (IX+01h),00h
                    ;        ;MEM[IY+0x01] = 0x00   ;                                  ;                             //      LD      (IY+01h),00h
                    ;        ;IY = 0xBB00             ;                                  ;                             //      LD      IY,BB00h
                    ;        ;DE = 0x0004             ;                                  ;                             //      LD      DE,0004h
                    ;        ;H = 0xFF              ;                                  ;                             //      LD      H,FFh
                    ;        ;A = 0x27              ;                                  ;                             //      LD      A,27h
                    ;        ;IO[BC] = A            ;                                  ;                             //      !OUT     (C),A
                    ;        ;GOS(*(sp++) = (int)&&C9C4;goto RMC926;C9C4:a=a;)               ;                             //      CALL    RMC926
//      POP     DE                             ////      POP     DE
sp--;cnt_sp--;                             ////c:sp--;cnt_sp--;
                    ;        ;RET(goto **(--sp);)         ;                                  ;                             //      RET
RMC9C9:                             //RMC9C9:
a = A - 0x80        ;f=a     ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;                             //      CP      80h
        ;if ( !F.C ) goto RMCA8E   ;                                  ;                                   //      JP      NC,RMCA8E
a = A - 0x69        ;f=a     ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;                             //      CP      69h
        ;if (  F.C ) goto RMCA8E   ;                                  ;                                   //      JP      C,RMCA8E
                    ;        ;A = 0x20              ;                                  ;                             //      LD      A,20h
                    ;        ;RMB60F[0] = A             ;                                  ;                             //      LD      (RMB60F),A
                    ;        ;IY = 0xB600             ;                                  ;                             //      LD      IY,B600h
                    ;        ;A = D                 ;                                  ;                             //      LD      A,D
a = A - 0x6A        ;f=a     ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;                             //      CP      6Ah
                    ;        ;if (  F.Z ) {goto RMC9EB;}else{}               ;                                   //      JR      Z,RMC9EB
a = A - 0x6B        ;f=a     ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;                             //      CP      6Bh
                    ;        ;if (  F.Z ) {goto RMC9EB;}else{}               ;                                   //      JR      Z,RMC9EB
a = MEM[IY+0x04] - 1;f=a&0xff;MEM[IY+0x04] = a      ;F.Z=((a&0xff)==0)  ;              ;                             //      DEC     (IY+04h)
                    ;        ;goto RMC837               ;                                  ;                             //      JP      RMC837
RMC9EB:                             //RMC9EB:
a = MEM[IY+0x19] - 1;f=a&0xff;MEM[IY+0x19] = a      ;F.Z=((a&0xff)==0)  ;              ;                             //      DEC     (IY+19h)
                    ;        ;goto RMC837               ;                                  ;                             //      JP      RMC837
RMC9F1:                             //RMC9F1:
a = A - 0xE0        ;f=a     ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;                             //      CP      E0h
        ;if ( !F.C ) goto RMCA8E   ;                                  ;                                   //      JP      NC,RMCA8E
                    ;        ;D = A                 ;                                  ;                             //      LD      D,A
                    ;        ;A = L                 ;                                  ;                             //      LD      A,L
a = A - 0x01        ;f=a     ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;                             //      CP      01h
        ;if (  F.Z ) goto RMC837   ;                                  ;                                   //      JP      Z,RMC837
                    ;        ;A = D                 ;                                  ;                             //      LD      A,D
a = A - 0xDF        ;f=a     ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;                             //      CP      DFh
                    ;        ;if (  F.Z ) {goto RMCA12;}else{}               ;                                   //      JR      Z,RMCA12
a = A & 0x0F        ;f=a&0xff;A = a                 ;F.Z=((a&0xff)==0)  ;F.C=0         ;                             //      AND     0Fh
a = A - 0x0E        ;f=a     ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;                             //      CP      0Eh
                    ;        ;A = D                 ;                                  ;                             //      LD      A,D
                    ;        ;if ( !F.C ) {goto RMCA1B;}else{}               ;                                   //      JR      NC,RMCA1B
a = A & 0x0F        ;f=a&0xff;A = a                 ;F.Z=((a&0xff)==0)  ;F.C=0         ;                             //      AND     0Fh
a = A - 0x0D        ;f=a     ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;                             //      CP      0Dh
                    ;        ;A = D                 ;                                  ;                             //      LD      A,D
                    ;        ;if (  F.Z ) {goto RMCA77;}else{}               ;                                   //      JR      Z,RMCA77
                    ;        ;goto RMCA34               ;                                  ;                             //      JR      RMCA34
RMCA12:                             //RMCA12:
                    ;        ;MEM[IX+0x00] = C      ;                                  ;                             //      LD      (IX+00h),C
                    ;        ;MEM[IX+0x01] = B      ;                                  ;                             //      LD      (IX+01h),B
                    ;        ;goto RMC837               ;                                  ;                             //      JP      RMC837
RMCA1B:                             //RMCA1B:
                    ;        ;BC = 0xAA06             ;                                  ;                             //      LD      BC,AA06h
a = B - 1           ;f=a&0xff;B = a                 ;F.Z=((a&0xff)==0)  ;              ;                             //      DEC     B
                    ;        ;A = 0x00              ;                                  ;                             //      LD      A,00h
                    ;        ;IO[BC] = A            ;                                  ;                             //      !OUT     (C),A
a = B + 1           ;f=a&0xff;B = a                 ;F.Z=((a&0xff)==0)  ;              ;                             //      INC     B
                    ;        ;IO[BC] = A            ;                                  ;                             //      !OUT     (C),A
a = B + 1           ;f=a&0xff;B = a                 ;F.Z=((a&0xff)==0)  ;              ;                             //      INC     B
                    ;        ;IO[BC] = A            ;                                  ;                             //      !OUT     (C),A
a = B - 1           ;f=a&0xff;B = a                 ;F.Z=((a&0xff)==0)  ;              ;                             //      DEC     B
                    ;        ;GOS(*(sp++) = (int)&&CA2A;goto RMC5A9;CA2A:a=a;)               ;                             //      CALL    RMC5A9
//      POP     DE                             ////      POP     DE
sp--;cnt_sp--;                             ////c:sp--;cnt_sp--;
                    ;        ;A = 0x70              ;                                  ;                             //      LD      A,70h
                    ;        ;GOS(*(sp++) = (int)&&CA30;goto RMCBCD;CA30:a=a;)               ;                             //      CALL    RMCBCD
                    ;        ;RET(goto **(--sp);)         ;                                  ;                             //      RET
RMCA34:                             //RMCA34:
a = A - 0xD0        ;f=a     ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;                             //      CP      D0h
                    ;        ;if (  F.C ) {goto RMCA39;}else{}               ;                                   //      JR      C,RMCA39
a = C - 1           ;f=a&0xff;C = a                 ;F.Z=((a&0xff)==0)  ;              ;                             //      DEC     C
RMCA39:                             //RMCA39:
                    ;        ;IY = 0xBF00             ;                                  ;                             //      LD      IY,BF00h
                    ;        ;DE = 0x0004             ;                                  ;                             //      LD      DE,0004h
                    ;        ;H = 0x20              ;                                  ;                             //      LD      H,20h
RMCA42:                             //RMCA42:
                    ;        ;A = B                 ;                                  ;                             //      LD      A,B
                    ;        ;GOS(*(sp++) = (int)&&CA43;goto RMC426;CA43:a=a;)               ;                             //      CALL    RMC426
                    ;        ;A = MEM[IY+0x00]      ;                                  ;                             //      LD      A,(IY+00h)
a = A - C           ;f=a     ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;                             //      CP      C
                    ;        ;if (  F.Z ) {goto RMCA56;}else{}               ;                                   //      JR      Z,RMCA56
                    ;        ;A = H                 ;                                  ;                             //      LD      A,H
a = A - 0x00        ;f=a     ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;                             //      CP      00h
                    ;        ;if (  F.Z ) {RET(goto **(--sp););}else{}          ;                                    //      RET     Z
a = H - 1           ;f=a&0xff;H = a                 ;F.Z=((a&0xff)==0)  ;              ;                             //      DEC     H
                    ;        ;if (  F.Z ) {RET(goto **(--sp););}else{}          ;                                    //      RET     Z
a = IY + DE         ;f=a     ;IY = a                ;                   ;F.C=a>>16     ;                             //      ADD     IY,DE
                    ;        ;goto RMCA42               ;                                  ;                             //      JR      RMCA42
RMCA56:                             //RMCA56:
                    ;        ;A = 0x03              ;                                  ;                             //      LD      A,03h
                    ;        ;GOS(*(sp++) = (int)&&CA58;goto RMCBCD;CA58:a=a;)               ;                             //      CALL    RMCBCD
a = MEM[IY+0x03] - 1;f=a&0xff;MEM[IY+0x03] = a      ;F.Z=((a&0xff)==0)  ;              ;                             //      DEC     (IY+03h)
        ;if ( !F.Z ) goto RMC837   ;                                  ;                                   //      JP      NZ,RMC837
                    ;        ;MEM[IY+0x01] = 0x00   ;                                  ;                             //      LD      (IY+01h),00h
                    ;        ;D = 0x00              ;                                  ;                             //      LD      D,00h
                    ;        ;IO[BC] = D            ;                                  ;                             //      !OUT     (C),D
a = C + 1           ;f=a&0xff;C = a                 ;F.Z=((a&0xff)==0)  ;              ;                             //      INC     C
                    ;        ;IO[BC] = D            ;                                  ;                             //      !OUT     (C),D
a = C - 1           ;f=a&0xff;C = a                 ;F.Z=((a&0xff)==0)  ;              ;                             //      DEC     C
                    ;        ;GOS(*(sp++) = (int)&&CA6D;goto RMC5A9;CA6D:a=a;)               ;                             //      CALL    RMC5A9
//      POP     DE                             ////      POP     DE
sp--;cnt_sp--;                             ////c:sp--;cnt_sp--;
                    ;        ;A = 0x47              ;                                  ;                             //      LD      A,47h
                    ;        ;GOS(*(sp++) = (int)&&CA73;goto RMCBCD;CA73:a=a;)               ;                             //      CALL    RMCBCD
                    ;        ;RET(goto **(--sp);)         ;                                  ;                             //      RET
RMCA77:                             //RMCA77:
a = A - 0xD0        ;f=a     ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;                             //      CP      D0h
                    ;        ;if (  F.C ) {goto RMCA7C;}else{}               ;                                   //      JR      C,RMCA7C
a = C - 1           ;f=a&0xff;C = a                 ;F.Z=((a&0xff)==0)  ;              ;                             //      DEC     C
RMCA7C:                             //RMCA7C:
                    ;        ;A = 0x60              ;                                  ;                             //      LD      A,60h
                    ;        ;GOS(*(sp++) = (int)&&CA7E;goto RMCBCD;CA7E:a=a;)               ;                             //      CALL    RMCBCD
                    ;        ;D = 0x00              ;                                  ;                             //      LD      D,00h
                    ;        ;IO[BC] = D            ;                                  ;                             //      !OUT     (C),D
a = C + 1           ;f=a&0xff;C = a                 ;F.Z=((a&0xff)==0)  ;              ;                             //      INC     C
                    ;        ;IO[BC] = D            ;                                  ;                             //      !OUT     (C),D
a = C - 1           ;f=a&0xff;C = a                 ;F.Z=((a&0xff)==0)  ;              ;                             //      DEC     C
                    ;        ;GOS(*(sp++) = (int)&&CA89;goto RMC5A9;CA89:a=a;)               ;                             //      CALL    RMC5A9
//      POP     DE                             ////      POP     DE
sp--;cnt_sp--;                             ////c:sp--;cnt_sp--;
                    ;        ;RET(goto **(--sp);)         ;                                  ;                             //      RET
RMCA8E:                             //RMCA8E:
                    ;        ;RET(goto **(--sp);)         ;                                  ;                             //      RET
                    ;        ;a=a                   ;                                  ;                             //      NOP
RMCA90:                             //RMCA90:
                    ;        ;A = RMB618[0]             ;                                  ;                             //      LD      A,(RMB618)
                    ;        ;BC = 0xD1AE             ;                                  ;                             //      LD      BC,D1AEh
a = A<<1            ;f=a&0xff;A = a                 ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;                             //      SLA     A
                    ;        ;GOS(*(sp++) = (int)&&CA98;goto RMCAC7;CA98:a=a;)               ;                             //      CALL    RMCAC7
                    ;        ;A = RMB615[0]             ;                                  ;                             //      LD      A,(RMB615)
                    ;        ;BC = 0xD1FE             ;                                  ;                             //      LD      BC,D1FEh
                    ;        ;GOS(*(sp++) = (int)&&CAA1;goto RMCAC7;CAA1:a=a;)               ;                             //      CALL    RMCAC7
                    ;        ;A = RMB619[0]             ;                                  ;                             //      LD      A,(RMB619)
                    ;        ;BC = 0xC24E             ;                                  ;                             //      LD      BC,C24Eh
                    ;        ;GOS(*(sp++) = (int)&&CAAA;goto RMCAEC;CAAA:a=a;)               ;                             //      CALL    RMCAEC
                    ;        ;A = RMB604[0]             ;                                  ;                             //      LD      A,(RMB604)
                    ;        ;BC = 0xC29E             ;                                  ;                             //      LD      BC,C29Eh
                    ;        ;GOS(*(sp++) = (int)&&CAB3;goto RMCAEC;CAB3:a=a;)               ;                             //      CALL    RMCAEC
                    ;        ;BC = 0xC2EE             ;                                  ;                             //      LD      BC,C2EEh
                    ;        ;D = 0x03              ;                                  ;                             //      LD      D,03h
                    ;        ;HL = 0xB607             ;                                  ;                             //      LD      HL,B607h
RMCABE:                             //RMCABE:
                    ;        ;A = MEM[HL]           ;                                  ;                             //      LD      A,(HL)
                    ;        ;GOS(*(sp++) = (int)&&CABF;goto RMCB0D;CABF:a=a;)               ;                             //      CALL    RMCB0D
                    ;        ;HL--                  ;                                  ;                             //      DEC     HL
a = D - 1           ;f=a&0xff;D = a                 ;F.Z=((a&0xff)==0)  ;              ;                             //      DEC     D
                    ;        ;if ( !F.Z ) {goto RMCABE;}else{}               ;                                   //      JR      NZ,RMCABE
                    ;        ;RET(goto **(--sp);)         ;                                  ;                             //      RET
RMCAC7:                             //RMCAC7:
                    ;        ;D = 0xFF              ;                                  ;                             //      LD      D,FFh
                    ;        ;E = 0x08              ;                                  ;                             //      LD      E,08h
RMCACB:                             //RMCACB:
a = A - 0x04        ;f=a     ;A = a                 ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;                             //      SUB     04h
                    ;        ;if (  F.C ) {goto RMCAD6;}else{}               ;                                   //      JR      C,RMCAD6
                    ;        ;IO[BC] = D            ;                                  ;                             //      !OUT     (C),D
                    ;        ;BC++                  ;                                  ;                             //      INC     BC
a = E - 1           ;f=a&0xff;E = a                 ;F.Z=((a&0xff)==0)  ;              ;                             //      DEC     E
                    ;        ;if ( !F.Z ) {goto RMCACB;}else{}               ;                                   //      JR      NZ,RMCACB
                    ;        ;RET(goto **(--sp);)         ;                                  ;                             //      RET
RMCAD6:                             //RMCAD6:
                    ;        ;D = 0xFC              ;                                  ;                             //      LD      D,FCh
RMCAD8:                             //RMCAD8:
a = A + 1           ;f=a&0xff;A = a                 ;F.Z=((a&0xff)==0)  ;              ;                             //      INC     A
                    ;        ;if (  F.Z ) {goto RMCAE1;}else{}               ;                                   //      JR      Z,RMCAE1
a = D<<1            ;f=a&0xff;D = a                 ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;                             //      SLA     D
a = D<<1            ;f=a&0xff;D = a                 ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;                             //      SLA     D
                    ;        ;goto RMCAD8               ;                                  ;                             //      JR      RMCAD8
RMCAE1:                             //RMCAE1:
                    ;        ;IO[BC] = D            ;                                  ;                             //      !OUT     (C),D
                    ;        ;D = 0x00              ;                                  ;                             //      LD      D,00h
RMCAE5:                             //RMCAE5:
                    ;        ;BC++                  ;                                  ;                             //      INC     BC
a = E - 1           ;f=a&0xff;E = a                 ;F.Z=((a&0xff)==0)  ;              ;                             //      DEC     E
                    ;        ;if (  F.Z ) {RET(goto **(--sp););}else{}          ;                                    //      RET     Z
                    ;        ;IO[BC] = D            ;                                  ;                             //      !OUT     (C),D
                    ;        ;goto RMCAE5               ;                                  ;                             //      JR      RMCAE5
RMCAEC:                             //RMCAEC:
                    ;        ;*(SP++)=HL            ;                                  ;                             //      PUSH    HL
                    ;        ;*(SP++)=DE            ;                                  ;                             //      PUSH    DE
                    ;        ;*(SP++)=BC            ;                                  ;                             //      PUSH    BC
a = A<<1            ;f=a&0xff;A = a                 ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;                             //      SLA     A
a = A<<1            ;f=a&0xff;A = a                 ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;                             //      SLA     A
a = A<<1            ;f=a&0xff;A = a                 ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;                             //      SLA     A
                    ;        ;D = 0x00              ;                                  ;                             //      LD      D,00h
                    ;        ;E = A                 ;                                  ;                             //      LD      E,A
                    ;        ;HL = 0xCB22             ;                                  ;                             //      LD      HL,CB22h
a = HL + DE         ;f=a     ;HL = a                ;                   ;F.C=a>>16     ;                             //      ADD     HL,DE
                    ;        ;D = 0x08              ;                                  ;                             //      LD      D,08h
RMCAFE:                             //RMCAFE:
                    ;        ;A = MEM[HL]           ;                                  ;                             //      LD      A,(HL)
                    ;        ;IO[BC] = A            ;                                  ;                             //      !OUT     (C),A
                    ;        ;HL++                  ;                                  ;                             //      INC     HL
                    ;        ;A = 0x08              ;                                  ;                             //      LD      A,08h
a = A + B           ;f=a&0xff;A = a                 ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;                             //      ADD     B
                    ;        ;B = A                 ;                                  ;                             //      LD      B,A
a = D - 1           ;f=a&0xff;D = a                 ;F.Z=((a&0xff)==0)  ;              ;                             //      DEC     D
                    ;        ;if ( !F.Z ) {goto RMCAFE;}else{}               ;                                   //      JR      NZ,RMCAFE
                    ;        ;BC=*(--SP)            ;                                  ;                             //      POP     BC
                    ;        ;DE=*(--SP)            ;                                  ;                             //      POP     DE
                    ;        ;HL=*(--SP)            ;                                  ;                             //      POP     HL
                    ;        ;RET(goto **(--sp);)         ;                                  ;                             //      RET
RMCB0D:                             //RMCB0D:
                    ;        ;*(SP++)=AF            ;                                  ;                             //      PUSH    AF
a = A               ;f=a&0xff;A=(a>>1)              ;F.Z=((a&0xff)==0)  ;F.C=a&1       ;                             //      SRL     A
a = A               ;f=a&0xff;A=(a>>1)              ;F.Z=((a&0xff)==0)  ;F.C=a&1       ;                             //      SRL     A
a = A               ;f=a&0xff;A=(a>>1)              ;F.Z=((a&0xff)==0)  ;F.C=a&1       ;                             //      SRL     A
a = A               ;f=a&0xff;A=(a>>1)              ;F.Z=((a&0xff)==0)  ;F.C=a&1       ;                             //      SRL     A
                    ;        ;GOS(*(sp++) = (int)&&CB16;goto RMCAEC;CB16:a=a;)               ;                             //      CALL    RMCAEC
                    ;        ;BC++                  ;                                  ;                             //      INC     BC
                    ;        ;AF=*(--SP)            ;                                  ;                             //      POP     AF
a = A & 0x0F        ;f=a&0xff;A = a                 ;F.Z=((a&0xff)==0)  ;F.C=0         ;                             //      AND     0Fh
                    ;        ;GOS(*(sp++) = (int)&&CB1D;goto RMCAEC;CB1D:a=a;)               ;                             //      CALL    RMCAEC
                    ;        ;BC++                  ;                                  ;                             //      INC     BC
                    ;        ;RET(goto **(--sp);)         ;                                  ;                             //      RET
RMCB72:                             //RMCB72:
                    ;        ;BC = 0x1C00             ;                                  ;                             //      LD      BC,1C00h
RMCB75:                             //RMCB75:
                    ;        ;A = RMB618[0]             ;                                  ;                             //      LD      A,(RMB618)
a = A + 0x24        ;f=a&0xff;A = a                 ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;                             //      ADD     24h
a = A - 0x2F        ;f=a     ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;                             //      CP      2Fh
                    ;        ;if (  F.C ) {goto RMCB80;}else{}               ;                                   //      JR      C,RMCB80
                    ;        ;A = 0x2E              ;                                  ;                             //      LD      A,2Eh
RMCB80:                             //RMCB80:
                    ;        ;E = 0x0B              ;                                  ;                             //      LD      E,0Bh
                    ;        ;IO[BC] = E            ;                                  ;                             //      !OUT     (C),E
a = B - 1           ;f=a&0xff;B = a                 ;F.Z=((a&0xff)==0)  ;              ;                             //      DEC     B
                    ;        ;IO[BC] = A            ;                                  ;                             //      !OUT     (C),A
a = B + 1           ;f=a&0xff;B = a                 ;F.Z=((a&0xff)==0)  ;              ;                             //      INC     B
                    ;        ;A = RMB60F[0]             ;                                  ;                             //      LD      A,(RMB60F)
a = A - 0x00        ;f=a     ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;                             //      CP      00h
                    ;        ;if (  F.Z ) {goto RMCB90;}else{}               ;                                   //      JR      Z,RMCB90
a = A - 1           ;f=a&0xff;A = a                 ;F.Z=((a&0xff)==0)  ;              ;                             //      DEC     A
RMCB90:                             //RMCB90:
                    ;        ;RMB60F[0] = A             ;                                  ;                             //      LD      (RMB60F),A
a = A - 0x20        ;f=a     ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;                             //      CP      20h
                    ;        ;if (  F.C ) {goto RMCB99;}else{}               ;                                   //      JR      C,RMCB99
                    ;        ;A = 0x1F              ;                                  ;                             //      LD      A,1Fh
RMCB99:                             //RMCB99:
                    ;        ;E = 0x09              ;                                  ;                             //      LD      E,09h
                    ;        ;IO[BC] = E            ;                                  ;                             //      !OUT     (C),E
a = B - 1           ;f=a&0xff;B = a                 ;F.Z=((a&0xff)==0)  ;              ;                             //      DEC     B
a = A               ;f=a&0xff;A=(a>>1)              ;F.Z=((a&0xff)==0)  ;F.C=a&1       ;                             //      SRL     A
                    ;        ;IO[BC] = A            ;                                  ;                             //      !OUT     (C),A
a = B + 1           ;f=a&0xff;B = a                 ;F.Z=((a&0xff)==0)  ;              ;                             //      INC     B
                    ;        ;D = 0x00              ;                                  ;                             //      LD      D,00h
                    ;        ;IX = 0xBA00             ;                                  ;                             //      LD      IX,BA00h
                    ;        ;E = 0x04              ;                                  ;                             //      LD      E,04h
RMCBAB:                             //RMCBAB:
                    ;        ;A = MEM[IX+0x01]      ;                                  ;                             //      LD      A,(IX+01h)
a = A - 0x00        ;f=a     ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;                             //      CP      00h
                    ;        ;if (  F.Z ) {goto RMCBB9;}else{}               ;                                   //      JR      Z,RMCBB9
                    ;        ;A = MEM[IX+0x03]      ;                                  ;                             //      LD      A,(IX+03h)
a = A - D           ;f=a     ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;                             //      CP      D
                    ;        ;if (  F.C ) {goto RMCBB9;}else{}               ;                                   //      JR      C,RMCBB9
                    ;        ;D = A                 ;                                  ;                             //      LD      D,A
RMCBB9:                             //RMCBB9:
                    ;        ;IX++                  ;                                  ;                             //      INC     IX
                    ;        ;IX++                  ;                                  ;                             //      INC     IX
                    ;        ;IX++                  ;                                  ;                             //      INC     IX
                    ;        ;IX++                  ;                                  ;                             //      INC     IX
a = E - 1           ;f=a&0xff;E = a                 ;F.Z=((a&0xff)==0)  ;              ;                             //      DEC     E
                    ;        ;if ( !F.Z ) {goto RMCBAB;}else{}               ;                                   //      JR      NZ,RMCBAB
                    ;        ;A = D                 ;                                  ;                             //      LD      A,D
                    ;        ;E = 0x0A              ;                                  ;                             //      LD      E,0Ah
                    ;        ;IO[BC] = E            ;                                  ;                             //      !OUT     (C),E
a = B - 1           ;f=a&0xff;B = a                 ;F.Z=((a&0xff)==0)  ;              ;                             //      DEC     B
                    ;        ;IO[BC] = A            ;                                  ;                             //      !OUT     (C),A
                    ;        ;RET(goto **(--sp);)         ;                                  ;                             //      RET
RMCBCD:                             //RMCBCD:
                    ;        ;*(SP++)=HL            ;                                  ;                             //      PUSH    HL
                    ;        ;HL = 0xB605             ;                                  ;                             //      LD      HL,B605h
a = A + MEM[HL]     ;f=a&0xff;A = a                 ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;                             //      ADD     (HL)
//DAA not support                                                             ;                             //      DAA
                    ;        ;MEM[HL] = A           ;                                  ;                             //      LD      (HL),A
                    ;        ;HL++                  ;                                  ;                             //      INC     HL
                    ;        ;A = MEM[HL]           ;                                  ;                             //      LD      A,(HL)
a = A + 0x00 + F.C  ;f=a&0xff;A = a                 ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;                             //      ADC     00h
//DAA not support                                                             ;                             //      DAA
                    ;        ;MEM[HL] = A           ;                                  ;                             //      LD      (HL),A
                    ;        ;HL++                  ;                                  ;                             //      INC     HL
                    ;        ;A = MEM[HL]           ;                                  ;                             //      LD      A,(HL)
a = A + 0x00 + F.C  ;f=a&0xff;A = a                 ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;                             //      ADC     00h
//DAA not support                                                             ;                             //      DAA
                    ;        ;MEM[HL] = A           ;                                  ;                             //      LD      (HL),A
                    ;        ;HL = 0xB60F             ;                                  ;                             //      LD      HL,B60Fh
                    ;        ;MEM[HL] = 0x20        ;                                  ;                             //      LD      (HL),20h
                    ;        ;HL=*(--SP)            ;                                  ;                             //      POP     HL
                    ;        ;RET(goto **(--sp);)         ;                                  ;                             //      RET
                    ;        ;a=a                   ;                                  ;                             //      NOP
RMCBE8:                             //RMCBE8:
                    ;        ;IX = 0xBF70             ;                                  ;                             //      LD      IX,BF70h
                    ;        ;E = 0x04              ;                                  ;                             //      LD      E,04h
RMCBEE:                             //RMCBEE:
                    ;        ;A = MEM[IX+0x01]      ;                                  ;                             //      LD      A,(IX+01h)
a = A - 0x00        ;f=a     ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;                             //      CP      00h
        ;if ( !F.Z ) {GOS(*(sp++) = (int)&&CBF3;goto RMCC02;CBF3:a=a;);};                                   //      CALL    NZ,RMCC02
                    ;        ;IX++                  ;                                  ;                             //      INC     IX
                    ;        ;IX++                  ;                                  ;                             //      INC     IX
                    ;        ;IX++                  ;                                  ;                             //      INC     IX
                    ;        ;IX++                  ;                                  ;                             //      INC     IX
a = E - 1           ;f=a&0xff;E = a                 ;F.Z=((a&0xff)==0)  ;              ;                             //      DEC     E
                    ;        ;if ( !F.Z ) {goto RMCBEE;}else{}               ;                                   //      JR      NZ,RMCBEE
                    ;        ;RET(goto **(--sp);)         ;                                  ;                             //      RET
RMCC02:                             //RMCC02:
                    ;        ;C = MEM[IX+0x00]      ;                                  ;                             //      LD      C,(IX+00h)
                    ;        ;B = MEM[IX+0x01]      ;                                  ;                             //      LD      B,(IX+01h)
                    ;        ;*(SP++)=BC            ;                                  ;                             //      PUSH    BC
                    ;        ;IY=*(--SP)            ;                                  ;                             //      POP     IY
a = MEM[IX+0x02] - 1;f=a&0xff;MEM[IX+0x02] = a      ;F.Z=((a&0xff)==0)  ;              ;                             //      DEC     (IX+02h)
                    ;        ;A = 0x07              ;                                  ;                             //      LD      A,07h
a = A & MEM[IX+0x02];f=a&0xff;A = a                 ;F.Z=((a&0xff)==0)  ;F.C=0         ;                             //      AND     (IX+02h)
                    ;        ;if ( !F.Z ) {goto RMCC1A;}else{}               ;                                   //      JR      NZ,RMCC1A
a = rand()          ;f=a&0xff;A = a                 ;F.Z=((a&0xff)==0)  ;              ;                             //      LD      A,R
                    ;        ;MEM[IX+0x02] = A      ;                                  ;                             //      LD      (IX+02h),A
RMCC1A:                             //RMCC1A:
                    ;        ;A = MEM[IX+0x02]      ;                                  ;                             //      LD      A,(IX+02h)
a = A & (1<<3)     ;f=a&0xff;                      ;F.Z=((a&0xff)==0)  ;              ;                             //      BIT     3,A
                    ;        ;if (  F.Z ) {goto RMCC23;}else{}               ;                                   //      JR      Z,RMCC23
a = B - 1           ;f=a&0xff;B = a                 ;F.Z=((a&0xff)==0)  ;              ;                             //      DEC     B
a = B - 1           ;f=a&0xff;B = a                 ;F.Z=((a&0xff)==0)  ;              ;                             //      DEC     B
RMCC23:                             //RMCC23:
a = B + 1           ;f=a&0xff;B = a                 ;F.Z=((a&0xff)==0)  ;              ;                             //      INC     B
a = IO[BC]          ;f=a&0xff;A = a                 ;F.Z=((a&0xff)==0)  ;              ;                             //      !IN      A,(C)
                    ;        ;if ( !F.Z ) {RET(goto **(--sp););}else{}          ;                                    //      RET     NZ
a = C + 1           ;f=a&0xff;C = a                 ;F.Z=((a&0xff)==0)  ;              ;                             //      INC     C
a = IO[BC]          ;f=a&0xff;A = a                 ;F.Z=((a&0xff)==0)  ;              ;                             //      !IN      A,(C)
                    ;        ;if ( !F.Z ) {RET(goto **(--sp););}else{}          ;                                    //      RET     NZ
a = C - 1           ;f=a&0xff;C = a                 ;F.Z=((a&0xff)==0)  ;              ;                             //      DEC     C
                    ;        ;MEM[IX+0x01] = B      ;                                  ;                             //      LD      (IX+01h),B
                    ;        ;HL = 0xC3D3             ;                                  ;                             //      LD      HL,C3D3h
                    ;        ;IO[BC] = H            ;                                  ;                             //      !OUT     (C),H
a = C + 1           ;f=a&0xff;C = a                 ;F.Z=((a&0xff)==0)  ;              ;                             //      INC     C
                    ;        ;IO[BC] = L            ;                                  ;                             //      !OUT     (C),L
                    ;        ;*(SP++)=IY            ;                                  ;                             //      PUSH    IY
                    ;        ;BC=*(--SP)            ;                                  ;                             //      POP     BC
                    ;        ;A = 0x00              ;                                  ;                             //      LD      A,00h
                    ;        ;IO[BC] = A            ;                                  ;                             //      !OUT     (C),A
a = C + 1           ;f=a&0xff;C = a                 ;F.Z=((a&0xff)==0)  ;              ;                             //      INC     C
                    ;        ;IO[BC] = A            ;                                  ;                             //      !OUT     (C),A
                    ;        ;RET(goto **(--sp);)         ;                                  ;                             //      RET
RMCC42:                             //RMCC42:
                    ;        ;IX = 0xBF80             ;                                  ;                             //      LD      IX,BF80h
                    ;        ;E = 0x10              ;                                  ;                             //      LD      E,10h
RMCC48:                             //RMCC48:
                    ;        ;A = MEM[IX+0x01]      ;                                  ;                             //      LD      A,(IX+01h)
a = A - 0x00        ;f=a     ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;                             //      CP      00h
        ;if ( !F.Z ) {GOS(*(sp++) = (int)&&CC4D;goto RMCC58;CC4D:a=a;);};                                   //      CALL    NZ,RMCC58
                    ;        ;IX++                  ;                                  ;                             //      INC     IX
                    ;        ;IX++                  ;                                  ;                             //      INC     IX
a = E - 1           ;f=a&0xff;E = a                 ;F.Z=((a&0xff)==0)  ;              ;                             //      DEC     E
                    ;        ;if ( !F.Z ) {goto RMCC48;}else{}               ;                                   //      JR      NZ,RMCC48
                    ;        ;RET(goto **(--sp);)         ;                                  ;                             //      RET
RMCC58:                             //RMCC58:
                    ;        ;HL = 0xB610             ;                                  ;                             //      LD      HL,B610h
                    ;        ;A = MEM[IX+0x00]      ;                                  ;                             //      LD      A,(IX+00h)
a = A - MEM[HL]     ;f=a     ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;                             //      CP      (HL)
                    ;        ;if ( !F.Z ) {RET(goto **(--sp););}else{}          ;                                    //      RET     NZ
                    ;        ;HL++                  ;                                  ;                             //      INC     HL
                    ;        ;A = MEM[IX+0x01]      ;                                  ;                             //      LD      A,(IX+01h)
a = A - 1           ;f=a&0xff;A = a                 ;F.Z=((a&0xff)==0)  ;              ;                             //      DEC     A
a = A - 1           ;f=a&0xff;A = a                 ;F.Z=((a&0xff)==0)  ;              ;                             //      DEC     A
a = A - MEM[HL]     ;f=a     ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;                             //      CP      (HL)
                    ;        ;if ( !F.Z ) {RET(goto **(--sp););}else{}          ;                                    //      RET     NZ
                    ;        ;IY = 0xB610             ;                                  ;                             //      LD      IY,B610h
                    ;        ;MEM[IY+0x03] = 0xF9   ;                                  ;                             //      LD      (IY+03h),F9h
a = MEM[IY+0x09] - 1;f=a&0xff;MEM[IY+0x09] = a      ;F.Z=((a&0xff)==0)  ;              ;                             //      DEC     (IY+09h)
                    ;        ;C = MEM[IX+0x00]      ;                                  ;                             //      LD      C,(IX+00h)
                    ;        ;B = MEM[IX+0x01]      ;                                  ;                             //      LD      B,(IX+01h)
                    ;        ;MEM[IX+0x01] = 0x00   ;                                  ;                             //      LD      (IX+01h),00h
                    ;        ;HL = 0xFDFE             ;                                  ;                             //      LD      HL,FDFEh
a = C - 1           ;f=a&0xff;C = a                 ;F.Z=((a&0xff)==0)  ;              ;                             //      DEC     C
                    ;        ;IO[BC] = H            ;                                  ;                             //      !OUT     (C),H
                    ;        ;A = 0x2A              ;                                  ;                             //      LD      A,2Ah
a = C + 1           ;f=a&0xff;C = a                 ;F.Z=((a&0xff)==0)  ;              ;                             //      INC     C
                    ;        ;IO[BC] = A            ;                                  ;                             //      !OUT     (C),A
                    ;        ;IY = 0xBB00             ;                                  ;                             //      LD      IY,BB00h
                    ;        ;*(SP++)=DE            ;                                  ;                             //      PUSH    DE
                    ;        ;DE = 0x0004             ;                                  ;                             //      LD      DE,0004h
                    ;        ;H = 0xFF              ;                                  ;                             //      LD      H,FFh
                    ;        ;GOS(*(sp++) = (int)&&CC92;goto RMC926;CC92:a=a;)               ;                             //      CALL    RMC926
                    ;        ;A = 0x26              ;                                  ;                             //      LD      A,26h
a = C + 1           ;f=a&0xff;C = a                 ;F.Z=((a&0xff)==0)  ;              ;                             //      INC     C
                    ;        ;IO[BC] = A            ;                                  ;                             //      !OUT     (C),A
                    ;        ;GOS(*(sp++) = (int)&&CC9A;goto RMC926;CC9A:a=a;)               ;                             //      CALL    RMC926
                    ;        ;DE=*(--SP)            ;                                  ;                             //      POP     DE
a = C + 1           ;f=a&0xff;C = a                 ;F.Z=((a&0xff)==0)  ;              ;                             //      INC     C
                    ;        ;IO[BC] = L            ;                                  ;                             //      !OUT     (C),L
a = C - 1           ;f=a&0xff;C = a                 ;F.Z=((a&0xff)==0)  ;              ;                             //      DEC     C
a = C - 1           ;f=a&0xff;C = a                 ;F.Z=((a&0xff)==0)  ;              ;                             //      DEC     C
                    ;        ;*(SP++)=BC            ;                                  ;                             //      PUSH    BC
                    ;        ;*(SP++)=HL            ;                                  ;                             //      PUSH    HL
                    ;        ;*(SP++)=IX            ;                                  ;                             //      PUSH    IX
                    ;        ;IX = 0xB610             ;                                  ;                             //      LD      IX,B610h
                    ;        ;GOS(*(sp++) = (int)&&CCAB;goto RMC00D;CCAB:a=a;)               ;                             //      CALL    RMC00D
                    ;        ;IX=*(--SP)            ;                                  ;                             //      POP     IX
                    ;        ;HL=*(--SP)            ;                                  ;                             //      POP     HL
                    ;        ;BC=*(--SP)            ;                                  ;                             //      POP     BC
                    ;        ;A = 0x00              ;                                  ;                             //      LD      A,00h
                    ;        ;GOS(*(sp++) = (int)&&CCB4;goto RMCBCD;CCB4:a=a;)               ;                             //      CALL    RMCBCD
                    ;        ;RET(goto **(--sp);)         ;                                  ;                             //      RET
                    ;        ;a=a                   ;                                  ;                             //      NOP


RMCCB9:                             //RMCCB9:
                    ;        ;BC = 0x3000             ;                                  ;                             //      LD      BC,3000h
                    ;        ;IX = 0xB600             ;                                  ;                             //      LD      IX,B600h
a=B;B=_B;_B=a; a=C;C=_C;_C=a; a=D;D=_D;_D=a; a=E;E=_E;_E=a; a=H;H=_H;_H=a; a=L;L=_L;_L=a;                             //      EXX
                    ;        ;C = RMB600[0];B = RMB600[1]   ;                                  ;                             //      LD      BC,(RMB600)
RMCCC5:                             //RMCCC5:
                    ;        ;A = RMB611[0]             ;                                  ;                             //      LD      A,(RMB611)
a = A - 0x46        ;f=a     ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;                             //      CP      46h
                    ;        ;if ( !F.C ) {goto RMCCCE;}else{}               ;                                   //      JR      NC,RMCCCE
                    ;        ;A = 0x46              ;                                  ;                             //      LD      A,46h
RMCCCE:                             //RMCCCE:
a = A - 0xB9        ;f=a     ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;                             //      CP      B9h
                    ;        ;if (  F.C ) {goto RMCCD4;}else{}               ;                                   //      JR      C,RMCCD4
                    ;        ;A = 0xB9              ;                                  ;                             //      LD      A,B9h
RMCCD4:                             //RMCCD4:
a = A - B           ;f=a     ;A = a                 ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;                             //      SUB     B
                    ;        ;if (  F.C ) {goto RMCCFE;}else{}               ;                                   //      JR      C,RMCCFE
a = A - 0x06        ;f=a     ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;                             //      CP      06h
                    ;        ;if ( !F.C ) {goto RMCCDE;}else{}               ;                                   //      JR      NC,RMCCDE
a = B - 1           ;f=a&0xff;B = a                 ;F.Z=((a&0xff)==0)  ;              ;                             //      DEC     B
                    ;        ;goto RMCCC5               ;                                  ;                             //      JR      RMCCC5
RMCCDE:                             //RMCCDE:
a = A - 0x13        ;f=a     ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;                             //      CP      13h
                    ;        ;if (  F.C ) {goto RMCCE5;}else{}               ;                                   //      JR      C,RMCCE5
a = B + 1           ;f=a&0xff;B = a                 ;F.Z=((a&0xff)==0)  ;              ;                             //      INC     B
                    ;        ;goto RMCCC5               ;                                  ;                             //      JR      RMCCC5
RMCCE5:                             //RMCCE5:
                    ;        ;A = RMB610[0]             ;                                  ;                             //      LD      A,(RMB610)
a = A - C           ;f=a     ;A = a                 ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;                             //      SUB     C
                    ;        ;E = MEM[IX+0x12]      ;                                  ;                             //      LD      E,(IX+12h)
a = E & (1<<7)     ;f=a&0xff;                      ;F.Z=((a&0xff)==0)  ;              ;                             //      BIT     7,E
                    ;        ;if (  F.Z ) {goto RMCCF7;}else{}               ;                                   //      JR      Z,RMCCF7
a = A - 0x10        ;f=a     ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;                             //      CP      10h
                    ;        ;if ( !F.C ) {goto RMCCFE;}else{}               ;                                   //      JR      NC,RMCCFE
a = C - 1           ;f=a&0xff;C = a                 ;F.Z=((a&0xff)==0)  ;              ;                             //      DEC     C
                    ;        ;goto RMCCE5               ;                                  ;                             //      JR      RMCCE5
RMCCF7:                             //RMCCF7:
a = A - 0x22        ;f=a     ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;                             //      CP      22h
                    ;        ;if (  F.C ) {goto RMCCFE;}else{}               ;                                   //      JR      C,RMCCFE
a = C + 1           ;f=a&0xff;C = a                 ;F.Z=((a&0xff)==0)  ;              ;                             //      INC     C
                    ;        ;goto RMCCE5               ;                                  ;                             //      JR      RMCCE5
RMCCFE:                             //RMCCFE:
                    ;        ;RMB600[0] = C;RMB600[1] = B   ;                                  ;                             //      LD      (RMB600),BC
                    ;        ;E = 0x19              ;                                  ;                             //      LD      E,19h
{                             ////c:{
int x = 0;                             ////c:int x = 0;
int y = 0;                             ////c:int y = 0;
RMCD04:                             //RMCD04:
                    ;        ;D = 0x28              ;                                  ;                             //      LD      D,28h
                    ;        ;C = MEM[IX+0x00]      ;                                  ;                             //      LD      C,(IX+00h)
RMCD09:                             //RMCD09:
a = IO[BC]          ;f=a&0xff;A = a                 ;F.Z=((a&0xff)==0)  ;              ;                             //      !IN      A,(C)
a = C + 1           ;f=a&0xff;C = a                 ;F.Z=((a&0xff)==0)  ;              ;                             //      INC     C
a=B;B=_B;_B=a; a=C;C=_C;_C=a; a=D;D=_D;_D=a; a=E;E=_E;_E=a; a=H;H=_H;_H=a; a=L;L=_L;_L=a;                             //      EXX
                    ;        ;IO[BC] = A            ;                                  ;                             //      !OUT     (C),A
g_text[y][x] =A;                             ////c:g_text[y][x] =A;
x++;                             ////c:x++;
if ( x >= 40 ){                             ////c:if ( x >= 40 ){
	x = 0;                             ////c:	x = 0;
	y++;                             ////c:	y++;
}                             ////c:}
                    ;        ;BC++                  ;                                  ;                             //      INC     BC
a=B;B=_B;_B=a; a=C;C=_C;_C=a; a=D;D=_D;_D=a; a=E;E=_E;_E=a; a=H;H=_H;_H=a; a=L;L=_L;_L=a;                             //      EXX
a = D - 1           ;f=a&0xff;D = a                 ;F.Z=((a&0xff)==0)  ;              ;                             //      DEC     D
                    ;        ;if ( !F.Z ) {goto RMCD09;}else{}               ;                                   //      JR      NZ,RMCD09
a = B + 1           ;f=a&0xff;B = a                 ;F.Z=((a&0xff)==0)  ;              ;                             //      INC     B
a = E - 1           ;f=a&0xff;E = a                 ;F.Z=((a&0xff)==0)  ;              ;                             //      DEC     E
                    ;        ;if ( !F.Z ) {goto RMCD04;}else{}               ;                                   //      JR      NZ,RMCD04
}                             ////c:}
                    ;        ;RET(goto **(--sp);)         ;                                  ;                             //      RET


RMCD19:                             //RMCD19:
                    ;        ;IX = 0xB640             ;                                  ;                             //      LD      IX,B640h
                    ;        ;HL = 0xD000             ;                                  ;                             //      LD      HL,D000h
                    ;        ;DE = 0x0010             ;                                  ;                             //      LD      DE,0010h
                    ;        ;B = 0x08              ;                                  ;                             //      LD      B,08h
RMCD25:                             //RMCD25:
                    ;        ;A = MEM[HL]           ;                                  ;                             //      LD      A,(HL)
                    ;        ;HL++                  ;                                  ;                             //      INC     HL
                    ;        ;C = MEM[HL]           ;                                  ;                             //      LD      C,(HL)
                    ;        ;HL++                  ;                                  ;                             //      INC     HL
                    ;        ;MEM[IX+0x00] = A      ;                                  ;                             //      LD      (IX+00h),A
                    ;        ;MEM[IX+0x01] = C      ;                                  ;                             //      LD      (IX+01h),C
                    ;        ;MEM[IX+0x07] = 0xA1   ;                                  ;                             //      LD      (IX+07h),A1h
                    ;        ;MEM[IX+0x09] = 0x04   ;                                  ;                             //      LD      (IX+09h),04h
                    ;        ;MEM[IX+0x0A] = A      ;                                  ;                             //      LD      (IX+0Ah),A
                    ;        ;MEM[IX+0x0B] = A      ;                                  ;                             //      LD      (IX+0Bh),A
a = IX + DE         ;f=a     ;IX = a                ;                   ;F.C=a>>16     ;                             //      ADD     IX,DE
                    ;        ;if ( --B > 0 ) {goto RMCD25;}else{}             ;                                    //      DJNZ    RMCD25
                    ;        ;B = 0x34              ;                                  ;                             //      LD      B,34h
RMCD43:                             //RMCD43:
                    ;        ;A = MEM[HL]           ;                                  ;                             //      LD      A,(HL)
                    ;        ;HL++                  ;                                  ;                             //      INC     HL
                    ;        ;C = MEM[HL]           ;                                  ;                             //      LD      C,(HL)
                    ;        ;HL++                  ;                                  ;                             //      INC     HL
                    ;        ;MEM[IX+0x00] = A      ;                                  ;                             //      LD      (IX+00h),A
                    ;        ;MEM[IX+0x01] = C      ;                                  ;                             //      LD      (IX+01h),C
                    ;        ;MEM[IX+0x07] = 0x81   ;                                  ;                             //      LD      (IX+07h),81h
                    ;        ;MEM[IX+0x09] = 0x02   ;                                  ;                             //      LD      (IX+09h),02h
                    ;        ;MEM[IX+0x0A] = A      ;                                  ;                             //      LD      (IX+0Ah),A
a = IX + DE         ;f=a     ;IX = a                ;                   ;F.C=a>>16     ;                             //      ADD     IX,DE
                    ;        ;if ( --B > 0 ) {goto RMCD43;}else{}             ;                                    //      DJNZ    RMCD43
                    ;        ;IX = 0xBF00             ;                                  ;                             //      LD      IX,BF00h
                    ;        ;DE = 0x0004             ;                                  ;                             //      LD      DE,0004h
                    ;        ;A = 0x0E              ;                                  ;                             //      LD      A,0Eh
RMCD65:                             //RMCD65:
                    ;        ;C = MEM[HL]           ;                                  ;                             //      LD      C,(HL)
                    ;        ;HL++                  ;                                  ;                             //      INC     HL
                    ;        ;B = MEM[HL]           ;                                  ;                             //      LD      B,(HL)
                    ;        ;HL++                  ;                                  ;                             //      INC     HL
                    ;        ;MEM[IX+0x00] = C      ;                                  ;                             //      LD      (IX+00h),C
                    ;        ;MEM[IX+0x01] = B      ;                                  ;                             //      LD      (IX+01h),B
                    ;        ;MEM[IX+0x03] = 0x02   ;                                  ;                             //      LD      (IX+03h),02h
                    ;        ;a=A;A=_A;_A=a;                                           ;                             //      EX      AF,AF'
                    ;        ;A = 0xC1              ;                                  ;                             //      LD      A,C1h
                    ;        ;IO[BC] = A            ;                                  ;                             //      !OUT     (C),A
a = C + 1           ;f=a&0xff;C = a                 ;F.Z=((a&0xff)==0)  ;              ;                             //      INC     C
                    ;        ;A = 0xD1              ;                                  ;                             //      LD      A,D1h
                    ;        ;IO[BC] = A            ;                                  ;                             //      !OUT     (C),A
                    ;        ;a=A;A=_A;_A=a;                                           ;                             //      EX      AF,AF'
a = IX + DE         ;f=a     ;IX = a                ;                   ;F.C=a>>16     ;                             //      ADD     IX,DE
a = A - 1           ;f=a&0xff;A = a                 ;F.Z=((a&0xff)==0)  ;              ;                             //      DEC     A
                    ;        ;if ( !F.Z ) {goto RMCD65;}else{}               ;                                   //      JR      NZ,RMCD65
                    ;        ;A = 0x0E              ;                                  ;                             //      LD      A,0Eh
RMCD85:                             //RMCD85:
                    ;        ;C = MEM[HL]           ;                                  ;                             //      LD      C,(HL)
                    ;        ;HL++                  ;                                  ;                             //      INC     HL
                    ;        ;B = MEM[HL]           ;                                  ;                             //      LD      B,(HL)
                    ;        ;HL++                  ;                                  ;                             //      INC     HL
                    ;        ;MEM[IX+0x00] = C      ;                                  ;                             //      LD      (IX+00h),C
                    ;        ;MEM[IX+0x01] = B      ;                                  ;                             //      LD      (IX+01h),B
                    ;        ;MEM[IX+0x03] = 0x01   ;                                  ;                             //      LD      (IX+03h),01h
                    ;        ;a=A;A=_A;_A=a;                                           ;                             //      EX      AF,AF'
                    ;        ;A = 0xC0              ;                                  ;                             //      LD      A,C0h
                    ;        ;IO[BC] = A            ;                                  ;                             //      !OUT     (C),A
a = C + 1           ;f=a&0xff;C = a                 ;F.Z=((a&0xff)==0)  ;              ;                             //      INC     C
                    ;        ;A = 0xD0              ;                                  ;                             //      LD      A,D0h
                    ;        ;IO[BC] = A            ;                                  ;                             //      !OUT     (C),A
                    ;        ;a=A;A=_A;_A=a;                                           ;                             //      EX      AF,AF'
a = IX + DE         ;f=a     ;IX = a                ;                   ;F.C=a>>16     ;                             //      ADD     IX,DE
a = A - 1           ;f=a&0xff;A = a                 ;F.Z=((a&0xff)==0)  ;              ;                             //      DEC     A
                    ;        ;if ( !F.Z ) {goto RMCD85;}else{}               ;                                   //      JR      NZ,RMCD85
                    ;        ;A = 0x04              ;                                  ;                             //      LD      A,04h
RMCDA5:                             //RMCDA5:
                    ;        ;C = MEM[HL]           ;                                  ;                             //      LD      C,(HL)
                    ;        ;HL++                  ;                                  ;                             //      INC     HL
                    ;        ;B = MEM[HL]           ;                                  ;                             //      LD      B,(HL)
                    ;        ;HL++                  ;                                  ;                             //      INC     HL
                    ;        ;MEM[IX+0x00] = C      ;                                  ;                             //      LD      (IX+00h),C
                    ;        ;MEM[IX+0x01] = B      ;                                  ;                             //      LD      (IX+01h),B
                    ;        ;MEM[IX+0x03] = 0x02   ;                                  ;                             //      LD      (IX+03h),02h
                    ;        ;a=A;A=_A;_A=a;                                           ;                             //      EX      AF,AF'
                    ;        ;A = 0xC3              ;                                  ;                             //      LD      A,C3h
                    ;        ;IO[BC] = A            ;                                  ;                             //      !OUT     (C),A
a = C + 1           ;f=a&0xff;C = a                 ;F.Z=((a&0xff)==0)  ;              ;                             //      INC     C
                    ;        ;A = 0xD3              ;                                  ;                             //      LD      A,D3h
                    ;        ;IO[BC] = A            ;                                  ;                             //      !OUT     (C),A
                    ;        ;a=A;A=_A;_A=a;                                           ;                             //      EX      AF,AF'
a = IX + DE         ;f=a     ;IX = a                ;                   ;F.C=a>>16     ;                             //      ADD     IX,DE
a = A - 1           ;f=a&0xff;A = a                 ;F.Z=((a&0xff)==0)  ;              ;                             //      DEC     A
                    ;        ;if ( !F.Z ) {goto RMCDA5;}else{}               ;                                   //      JR      NZ,RMCDA5
                    ;        ;A = 0x04              ;                                  ;                             //      LD      A,04h
                    ;        ;DE = 0xCDDD             ;                                  ;                             //      LD      DE,CDDDh
RMCDC8:                             //RMCDC8:
                    ;        ;C = MEM[HL]           ;                                  ;                             //      LD      C,(HL)
                    ;        ;HL++                  ;                                  ;                             //      INC     HL
                    ;        ;B = MEM[HL]           ;                                  ;                             //      LD      B,(HL)
                    ;        ;HL++                  ;                                  ;                             //      INC     HL
                    ;        ;IO[BC] = D            ;                                  ;                             //      !OUT     (C),D
a = C + 1           ;f=a&0xff;C = a                 ;F.Z=((a&0xff)==0)  ;              ;                             //      INC     C
                    ;        ;IO[BC] = E            ;                                  ;                             //      !OUT     (C),E
a = A - 1           ;f=a&0xff;A = a                 ;F.Z=((a&0xff)==0)  ;              ;                             //      DEC     A
                    ;        ;if ( !F.Z ) {goto RMCDC8;}else{}               ;                                   //      JR      NZ,RMCDC8
                    ;        ;C = 0x70              ;                                  ;                             //      LD      C,70h
                    ;        ;B = 0x40              ;                                  ;                             //      LD      B,40h
                    ;        ;D = 0xDF              ;                                  ;                             //      LD      D,DFh
                    ;        ;E = 0xF0              ;                                  ;                             //      LD      E,F0h
RMCDDC:                             //RMCDDC:
a = IO[BC]          ;f=a&0xff;A = a                 ;F.Z=((a&0xff)==0)  ;              ;                             //      !IN      A,(C)
a = A - E           ;f=a     ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;                             //      CP      E
                    ;        ;if ( !F.C ) {goto RMCDE3;}else{}               ;                                   //      JR      NC,RMCDE3
                    ;        ;IO[BC] = D            ;                                  ;                             //      !OUT     (C),D
RMCDE3:                             //RMCDE3:
a = B + 1           ;f=a&0xff;B = a                 ;F.Z=((a&0xff)==0)  ;              ;                             //      INC     B
                    ;        ;A = B                 ;                                  ;                             //      LD      A,B
a = A - 0xC0        ;f=a     ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;                             //      CP      C0h
                    ;        ;if (  F.C ) {goto RMCDDC;}else{}               ;                                   //      JR      C,RMCDDC
                    ;        ;DE = 0xF9FA             ;                                  ;                             //      LD      DE,F9FAh
                    ;        ;A = 0x10              ;                                  ;                             //      LD      A,10h
RMCDEE:                             //RMCDEE:
                    ;        ;C = MEM[HL]           ;                                  ;                             //      LD      C,(HL)
                    ;        ;HL++                  ;                                  ;                             //      INC     HL
                    ;        ;B = MEM[HL]           ;                                  ;                             //      LD      B,(HL)
                    ;        ;HL++                  ;                                  ;                             //      INC     HL
                    ;        ;IO[BC] = D            ;                                  ;                             //      !OUT     (C),D
a = C + 1           ;f=a&0xff;C = a                 ;F.Z=((a&0xff)==0)  ;              ;                             //      INC     C
                    ;        ;IO[BC] = E            ;                                  ;                             //      !OUT     (C),E
a = A - 1           ;f=a&0xff;A = a                 ;F.Z=((a&0xff)==0)  ;              ;                             //      DEC     A
                    ;        ;if ( !F.Z ) {goto RMCDEE;}else{}               ;                                   //      JR      NZ,RMCDEE
                    ;        ;HL = 0xD0C0             ;                                  ;                             //      LD      HL,D0C0h
                    ;        ;DE = 0xBF80             ;                                  ;                             //      LD      DE,BF80h
                    ;        ;BC = 0x0020             ;                                  ;                             //      LD      BC,0020h
do{MEM[DE++] = MEM[HL++]; BC--; }while( BC != 0 );          ;                                    //      LDIR
                    ;        ;RET(goto **(--sp);)         ;                                  ;                             //      RET
RMCE06:                             //RMCE06:
                    ;        ;BC = 0x2000             ;                                  ;                             //      LD      BC,2000h
                    ;        ;A = 0x27              ;                                  ;                             //      LD      A,27h
                    ;        ;D = 0x04              ;                                  ;                             //      LD      D,04h
                    ;        ;E = 0x00              ;                                  ;                             //      LD      E,00h
RMCE0F:                             //RMCE0F:
                    ;        ;IO[BC] = A            ;                                  ;                             //      !OUT     (C),A
                    ;        ;BC++                  ;                                  ;                             //      INC     BC
a = E - 1           ;f=a&0xff;E = a                 ;F.Z=((a&0xff)==0)  ;              ;                             //      DEC     E
                    ;        ;if ( !F.Z ) {goto RMCE0F;}else{}               ;                                   //      JR      NZ,RMCE0F
a = D - 1           ;f=a&0xff;D = a                 ;F.Z=((a&0xff)==0)  ;              ;                             //      DEC     D
                    ;        ;if ( !F.Z ) {goto RMCE0F;}else{}               ;                                   //      JR      NZ,RMCE0F
                    ;        ;HL = 0xB600             ;                                  ;                             //      LD      HL,B600h
                    ;        ;A = 0x00              ;                                  ;                             //      LD      A,00h
                    ;        ;D = 0x0A              ;                                  ;                             //      LD      D,0Ah
                    ;        ;E = 0x00              ;                                  ;                             //      LD      E,00h
RMCE21:                             //RMCE21:
                    ;        ;MEM[HL] = A           ;                                  ;                             //      LD      (HL),A
                    ;        ;HL++                  ;                                  ;                             //      INC     HL
a = E - 1           ;f=a&0xff;E = a                 ;F.Z=((a&0xff)==0)  ;              ;                             //      DEC     E
                    ;        ;if ( !F.Z ) {goto RMCE21;}else{}               ;                                   //      JR      NZ,RMCE21
a = D - 1           ;f=a&0xff;D = a                 ;F.Z=((a&0xff)==0)  ;              ;                             //      DEC     D
                    ;        ;if ( !F.Z ) {goto RMCE21;}else{}               ;                                   //      JR      NZ,RMCE21
                    ;        ;RET(goto **(--sp);)         ;                                  ;                             //      RET


RMCE2A:                             //RMCE2A:
                    ;        ;A = 0xFF              ;                                  ;                             //      LD      A,FFh
                    ;        ;IX = 0xD101             ;                                  ;                             //      LD      IX,D101h
                    ;        ;BC = 0x4000             ;                                  ;                             //      LD      BC,4000h
                    ;        ;L = RMD100[0];H = RMD100[1]   ;                                  ;                             //      LD      HL,(RMD100)
RMCE36:                             //RMCE36:
                    ;        ;IX++                  ;                                  ;                             //      INC     IX
                    ;        ;E = MEM[IX+0x00]      ;                                  ;                             //      LD      E,(IX+00h)
RMCE3B:                             //RMCE3B:
a = E - 1           ;f=a&0xff;E = a                 ;F.Z=((a&0xff)==0)  ;              ;                             //      DEC     E
                    ;        ;if (  F.Z ) {goto RMCE43;}else{}               ;                                   //      JR      Z,RMCE43
                    ;        ;IO[BC] = A            ;                                  ;                             //      !OUT     (C),A
                    ;        ;BC++                  ;                                  ;                             //      INC     BC
                    ;        ;goto RMCE3B               ;                                  ;                             //      JR      RMCE3B

RMCE43:                             //RMCE43:
                    ;        ;HL--                  ;                                  ;                             //      DEC     HL
                    ;        ;a=A;A=_A;_A=a;                                           ;                             //      EX      AF,AF'
                    ;        ;A = H                 ;                                  ;                             //      LD      A,H
a = A | L           ;f=a&0xff;A = a                 ;F.Z=((a&0xff)==0)  ;F.C=0         ;                             //      OR      L
                    ;        ;if (  F.Z ) {RET(goto **(--sp););}else{}          ;                                    //      RET     Z

                    ;        ;a=A;A=_A;_A=a;                                           ;                             //      EX      AF,AF'
                    ;        ;A = ~A                ;                                  ;                             //      CPL
                    ;        ;goto RMCE36               ;                                  ;                             //      JR      RMCE36

RMCE4C:                             //RMCE4C:
                    ;        ;BC = 0x4100             ;                                  ;                             //      LD      BC,4100h
RMCE4F:                             //RMCE4F:
a = IO[BC]          ;f=a&0xff;A = a                 ;F.Z=((a&0xff)==0)  ;              ;                             //      !IN      A,(C)
a = A - 0x00        ;f=a     ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;                             //      CP      00h
        ;if ( !F.Z ) {GOS(*(sp++) = (int)&&CE53;goto RMCE5D;CE53:a=a;);};                                   //      CALL    NZ,RMCE5D
                    ;        ;BC++                  ;                                  ;                             //      INC     BC
                    ;        ;A = B                 ;                                  ;                             //      LD      A,B
a = A - 0xBF        ;f=a     ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;                             //      CP      BFh
                    ;        ;if (  F.C ) {goto RMCE4F;}else{}               ;                                   //      JR      C,RMCE4F
                    ;        ;RET(goto **(--sp);)         ;                                  ;                             //      RET


RMCE5D:                             //RMCE5D:
                    ;        ;E = 0x00              ;                                  ;                             //      LD      E,00h
a = B - 1           ;f=a&0xff;B = a                 ;F.Z=((a&0xff)==0)  ;              ;                             //      DEC     B
a = IO[BC]          ;f=a&0xff;A = a                 ;F.Z=((a&0xff)==0)  ;              ;                             //      !IN      A,(C)
a = A - 0x00        ;f=a     ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;                             //      CP      00h
                    ;        ;if (  F.Z ) {goto RMCE68;}else{}               ;                                   //      JR      Z,RMCE68
                    ;        ;E |= (1<<0)          ;                                  ;                             //      SET     0,E
RMCE68:                             //RMCE68:
a = B + 1           ;f=a&0xff;B = a                 ;F.Z=((a&0xff)==0)  ;              ;                             //      INC     B
a = B + 1           ;f=a&0xff;B = a                 ;F.Z=((a&0xff)==0)  ;              ;                             //      INC     B
a = IO[BC]          ;f=a&0xff;A = a                 ;F.Z=((a&0xff)==0)  ;              ;                             //      !IN      A,(C)
a = A - 0x00        ;f=a     ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;                             //      CP      00h
                    ;        ;if (  F.Z ) {goto RMCE72;}else{}               ;                                   //      JR      Z,RMCE72
                    ;        ;E |= (1<<1)          ;                                  ;                             //      SET     1,E
RMCE72:                             //RMCE72:
a = B - 1           ;f=a&0xff;B = a                 ;F.Z=((a&0xff)==0)  ;              ;                             //      DEC     B
a = C - 1           ;f=a&0xff;C = a                 ;F.Z=((a&0xff)==0)  ;              ;                             //      DEC     C
a = IO[BC]          ;f=a&0xff;A = a                 ;F.Z=((a&0xff)==0)  ;              ;                             //      !IN      A,(C)
a = A - 0x00        ;f=a     ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;                             //      CP      00h
                    ;        ;if (  F.Z ) {goto RMCE7C;}else{}               ;                                   //      JR      Z,RMCE7C
                    ;        ;E |= (1<<2)          ;                                  ;                             //      SET     2,E
RMCE7C:                             //RMCE7C:
a = C + 1           ;f=a&0xff;C = a                 ;F.Z=((a&0xff)==0)  ;              ;                             //      INC     C
a = C + 1           ;f=a&0xff;C = a                 ;F.Z=((a&0xff)==0)  ;              ;                             //      INC     C
a = IO[BC]          ;f=a&0xff;A = a                 ;F.Z=((a&0xff)==0)  ;              ;                             //      !IN      A,(C)
a = A - 0x00        ;f=a     ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;                             //      CP      00h
                    ;        ;if (  F.Z ) {goto RMCE86;}else{}               ;                                   //      JR      Z,RMCE86
                    ;        ;E |= (1<<3)          ;                                  ;                             //      SET     3,E
RMCE86:                             //RMCE86:
a = C - 1           ;f=a&0xff;C = a                 ;F.Z=((a&0xff)==0)  ;              ;                             //      DEC     C
                    ;        ;D = 0x00              ;                                  ;                             //      LD      D,00h
                    ;        ;HL = 0xCE91             ;                                  ;                             //      LD      HL,CE91h
a = HL + DE         ;f=a     ;HL = a                ;                   ;F.C=a>>16     ;                             //      ADD     HL,DE
                    ;        ;A = MEM[HL]           ;                                  ;                             //      LD      A,(HL)
                    ;        ;IO[BC] = A            ;                                  ;                             //      !OUT     (C),A
                    ;        ;RET(goto **(--sp);)         ;                                  ;                             //      RET

RMCEA1_Initialize:                             //RMCEA1_Initialize:
                    ;        ;GOS(*(sp++) = (int)&&CEA1;goto RMCE06;CEA1:a=a;)               ;                             //      CALL    RMCE06
                    ;        ;GOS(*(sp++) = (int)&&CEA4;goto RMCE2A;CEA4:a=a;)               ;                             //      CALL    RMCE2A
                    ;        ;GOS(*(sp++) = (int)&&CEA7;goto RMCE4C;CEA7:a=a;)               ;                             //      CALL    RMCE4C
                    ;        ;GOS(*(sp++) = (int)&&CEAA;goto RMCD19;CEAA:a=a;)               ;                             //      CALL    RMCD19
                    ;        ;HL = 0xD0E0             ;                                  ;                             //      LD      HL,D0E0h
                    ;        ;DE = 0xB600             ;                                  ;                             //      LD      DE,B600h
                    ;        ;BC = 0x0020             ;                                  ;                             //      LD      BC,0020h
do{MEM[DE++] = MEM[HL++]; BC--; }while( BC != 0 );          ;                                    //      LDIR
                    ;        ;GOS(*(sp++) = (int)&&CEB8;goto RMC2CB;CEB8:a=a;)               ;                             //      CALL    RMC2CB
                    ;        ;GOS(*(sp++) = (int)&&CEBB;goto RMC55D;CEBB:a=a;)               ;                             //      CALL    RMC55D
                    ;        ;GOS(*(sp++) = (int)&&CEBE;goto RMCCB9;CEBE:a=a;)               ;                             //      CALL    RMCCB9
                    ;        ;BC = 0xA906             ;                                  ;                             //      LD      BC,A906h
                    ;        ;A = 0xCE              ;                                  ;                             //      LD      A,CEh
                    ;        ;IO[BC] = A            ;                                  ;                             //      !OUT     (C),A
a = B + 1           ;f=a&0xff;B = a                 ;F.Z=((a&0xff)==0)  ;              ;                             //      INC     B
a = A + 1           ;f=a&0xff;A = a                 ;F.Z=((a&0xff)==0)  ;              ;                             //      INC     A
                    ;        ;IO[BC] = A            ;                                  ;                             //      !OUT     (C),A
a = B + 1           ;f=a&0xff;B = a                 ;F.Z=((a&0xff)==0)  ;              ;                             //      INC     B
                    ;        ;A = 0xDE              ;                                  ;                             //      LD      A,DEh
                    ;        ;IO[BC] = A            ;                                  ;                             //      !OUT     (C),A
                    ;        ;BC = 0x1C00             ;                                  ;                             //      LD      BC,1C00h
                    ;        ;HL = 0xCEE9             ;                                  ;                             //      LD      HL,CEE9h
                    ;        ;A = 0x00              ;                                  ;                             //      LD      A,00h
RMCED9:                             //RMCED9:
                    ;        ;D = MEM[HL]           ;                                  ;                             //      LD      D,(HL)
                    ;        ;IO[BC] = A            ;                                  ;                             //      !OUT     (C),A
a = B - 1           ;f=a&0xff;B = a                 ;F.Z=((a&0xff)==0)  ;              ;                             //      DEC     B
                    ;        ;IO[BC] = D            ;                                  ;                             //      !OUT     (C),D
a = B + 1           ;f=a&0xff;B = a                 ;F.Z=((a&0xff)==0)  ;              ;                             //      INC     B
a = A - 0x0D        ;f=a     ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;                             //      CP      0Dh
                    ;        ;if (  F.Z ) {goto RMCEE8;}else{}               ;                                   //      JR      Z,RMCEE8
a = A + 1           ;f=a&0xff;A = a                 ;F.Z=((a&0xff)==0)  ;              ;                             //      INC     A
                    ;        ;HL++                  ;                                  ;                             //      INC     HL
                    ;        ;goto RMCED9               ;                                  ;                             //      JR      RMCED9
RMCEE8:                             //RMCEE8:
                    ;        ;RET(goto **(--sp);)         ;                                  ;                             //      RET
                    ;        ;a=a                   ;                                  ;                             //      NOP
                    ;        ;BC++                  ;                                  ;                             //      INC     BC
                    ;        ;a=a                   ;                                  ;                             //      NOP
                    ;        ;a=a                   ;                                  ;                             //      NOP
                    ;        ;a=a                   ;                                  ;                             //      NOP
                    ;        ;B = 0x1F              ;                                  ;                             //      LD      B,1Fh
                    ;        ;L = RM001F[0];H = RM001F[1]   ;                                  ;                             //      LD      HL,(RM001F)
                    ;        ;a=a                   ;                                  ;                             //      NOP
                    ;        ;L = 0x00              ;                                  ;                             //      LD      L,00h
                    ;        ;a=A;A=_A;_A=a;                                           ;                             //      EX      AF,AF'
                    ;        ;a=a                   ;                                  ;                             //      NOP
                    ;        ;a=a                   ;                                  ;                             //      NOP
                    ;        ;a=a                   ;                                  ;                             //      NOP
                    ;        ;a=a                   ;                                  ;                             //      NOP
                    ;        ;a=a                   ;                                  ;                             //      NOP
                    ;        ;a=a                   ;                                  ;                             //      NOP
                    ;        ;a=a                   ;                                  ;                             //      NOP
                    ;        ;a=a                   ;                                  ;                             //      NOP
                    ;        ;a=a                   ;                                  ;                             //      NOP
RMCF00:                             //RMCF00:
while(	sys.UpdateSys() ){cl=0;                             ////c:while(	sys.UpdateSys() ){cl=0;
                    ;        ;GOS(*(sp++) = (int)&&CF00;goto RMC2CB;CF00:a=a;)               ;                             //      CALL    RMC2CB
                    ;        ;GOS(*(sp++) = (int)&&CF03;goto RMC6E8;CF03:a=a;)               ;                             //      CALL    RMC6E8
                    ;        ;GOS(*(sp++) = (int)&&CF06;goto RMCC42;CF06:a=a;)               ;                             //      CALL    RMCC42
                    ;        ;GOS(*(sp++) = (int)&&CF09;goto RMCCB9;CF09:a=a;)               ;                             //      CALL    RMCCB9
                    ;        ;GOS(*(sp++) = (int)&&CF0C;goto RMC6B8;CF0C:a=a;)               ;                             //      CALL    RMC6B8
                    ;        ;GOS(*(sp++) = (int)&&CF0F;goto RMC76B;CF0F:a=a;)               ;                             //      CALL    RMC76B
                    ;        ;GOS(*(sp++) = (int)&&CF12;goto RMC55D;CF12:a=a;)               ;                             //      CALL    RMC55D
                    ;        ;GOS(*(sp++) = (int)&&CF15;goto RMCA90;CF15:a=a;)               ;                             //      CALL    RMCA90
                    ;        ;GOS(*(sp++) = (int)&&CF18;goto RMCB72;CF18:a=a;)               ;                             //      CALL    RMCB72
                    ;        ;GOS(*(sp++) = (int)&&CF1B;goto RMCF38;CF1B:a=a;)               ;                             //      CALL    RMCF38
                    ;        ;GOS(*(sp++) = (int)&&CF1E;goto RMCCB9;CF1E:a=a;)               ;                             //      CALL    RMCCB9
                    ;        ;GOS(*(sp++) = (int)&&CF21;goto RMCBE8;CF21:a=a;)               ;                             //      CALL    RMCBE8
                    ;        ;GOS(*(sp++) = (int)&&CF24;goto RMC57A;CF24:a=a;)               ;                             //      CALL    RMC57A
                    ;        ;GOS(*(sp++) = (int)&&CF27;goto RMC541;CF27:a=a;)               ;                             //      CALL    RMC541
                    ;        ;GOS(*(sp++) = (int)&&CF2A;goto RMC6B8;CF2A:a=a;)               ;                             //      CALL    RMC6B8
                    ;        ;GOS(*(sp++) = (int)&&CF2D;goto RMC76B;CF2D:a=a;)               ;                             //      CALL    RMC76B
                    ;        ;GOS(*(sp++) = (int)&&CF30;goto RMC60A;CF30:a=a;)               ;                             //      CALL    RMC60A
                    ;        ;GOS(*(sp++) = (int)&&CF33;goto RMCF38;CF33:a=a;)               ;                             //      CALL    RMCF38
//      JR      RMCF00                             ////      JR      RMCF00
	DrawScreen();                             ////c:	DrawScreen();
}                             ////c:}

RMCF38:                             //RMCF38:
                    ;        ;DE = 0x0000             ;                                  ;                             //      LD      DE,0000h
                    ;        ;HL = 0x0000             ;                                  ;                             //      LD      HL,0000h
                    ;        ;BC = 0x1000             ;                                  ;                             //      LD      BC,1000h
do{MEM[DE++] = MEM[HL++]; BC--; }while( BC != 0 );          ;                                    //      LDIR
                    ;        ;BC = 0xA906             ;                                  ;                             //      LD      BC,A906h
a = IO[BC]          ;f=a&0xff;A = a                 ;F.Z=((a&0xff)==0)  ;              ;                             //      !IN      A,(C)
a = A - 0x00        ;f=a     ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;                             //      CP      00h
                    ;        ;if (  F.Z ) {goto RMCF9B;}else{}               ;                                   //      JR      Z,RMCF9B
                    ;        ;A = RMB619[0]             ;                                  ;                             //      LD      A,(RMB619)
a = A - 1           ;f=a&0xff;A = a                 ;F.Z=((a&0xff)==0)  ;              ;                             //      DEC     A
a = A - 0x80        ;f=a     ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;                             //      CP      80h
                    ;        ;if ( !F.C ) {goto RMCF84;}else{}               ;                                   //      JR      NC,RMCF84
                    ;        ;A = RMB604[0]             ;                                  ;                             //      LD      A,(RMB604)
a = A - 1           ;f=a&0xff;A = a                 ;F.Z=((a&0xff)==0)  ;              ;                             //      DEC     A
a = A - 0x80        ;f=a     ;                      ;F.Z=((a&0xff)==0)  ;F.C=(a>>8)    ;                             //      CP      80h
                    ;        ;if (  F.C ) {RET(goto **(--sp););}else{}          ;                                    //      RET     C
                    ;        ;C = RMB602[0];B = RMB602[1]   ;                                  ;                             //      LD      BC,(RMB602)
                    ;        ;A = 0x2A              ;                                  ;                             //      LD      A,2Ah
                    ;        ;IO[BC] = A            ;                                  ;                             //      !OUT     (C),A
a = C + 1           ;f=a&0xff;C = a                 ;F.Z=((a&0xff)==0)  ;              ;                             //      INC     C
                    ;        ;A = 0x2B              ;                                  ;                             //      LD      A,2Bh
                    ;        ;IO[BC] = A            ;                                  ;                             //      !OUT     (C),A
a = C + 1           ;f=a&0xff;C = a                 ;F.Z=((a&0xff)==0)  ;              ;                             //      INC     C
                    ;        ;IO[BC] = A            ;                                  ;                             //      !OUT     (C),A
a = C + 1           ;f=a&0xff;C = a                 ;F.Z=((a&0xff)==0)  ;              ;                             //      INC     C
                    ;        ;A = 0x26              ;                                  ;                             //      LD      A,26h
                    ;        ;IO[BC] = A            ;                                  ;                             //      !OUT     (C),A
a = B + 1           ;f=a&0xff;B = a                 ;F.Z=((a&0xff)==0)  ;              ;                             //      INC     B
                    ;        ;A = 0x24              ;                                  ;                             //      LD      A,24h
                    ;        ;IO[BC] = A            ;                                  ;                             //      !OUT     (C),A
a = C - 1           ;f=a&0xff;C = a                 ;F.Z=((a&0xff)==0)  ;              ;                             //      DEC     C
                    ;        ;A = 0x2E              ;                                  ;                             //      LD      A,2Eh
                    ;        ;IO[BC] = A            ;                                  ;                             //      !OUT     (C),A
a = C - 1           ;f=a&0xff;C = a                 ;F.Z=((a&0xff)==0)  ;              ;                             //      DEC     C
                    ;        ;IO[BC] = A            ;                                  ;                             //      !OUT     (C),A
a = C - 1           ;f=a&0xff;C = a                 ;F.Z=((a&0xff)==0)  ;              ;                             //      DEC     C
                    ;        ;A = 0x28              ;                                  ;                             //      LD      A,28h
                    ;        ;IO[BC] = A            ;                                  ;                             //      !OUT     (C),A
                    ;        ;goto RMCF9B               ;                                  ;                             //      JR      RMCF9B
RMCF84:                             //RMCF84:
                    ;        ;C = RMB610[0];B = RMB610[1]   ;                                  ;                             //      LD      BC,(RMB610)
                    ;        ;A = 0x2A              ;                                  ;                             //      LD      A,2Ah
                    ;        ;IO[BC] = A            ;                                  ;                             //      !OUT     (C),A
a = C + 1           ;f=a&0xff;C = a                 ;F.Z=((a&0xff)==0)  ;              ;                             //      INC     C
                    ;        ;A = 0x26              ;                                  ;                             //      LD      A,26h
                    ;        ;IO[BC] = A            ;                                  ;                             //      !OUT     (C),A
a = B + 1           ;f=a&0xff;B = a                 ;F.Z=((a&0xff)==0)  ;              ;                             //      INC     B
                    ;        ;A = 0x24              ;                                  ;                             //      LD      A,24h
                    ;        ;IO[BC] = A            ;                                  ;                             //      !OUT     (C),A
a = C - 1           ;f=a&0xff;C = a                 ;F.Z=((a&0xff)==0)  ;              ;                             //      DEC     C
                    ;        ;A = 0x28              ;                                  ;                             //      LD      A,28h
                    ;        ;IO[BC] = A            ;                                  ;                             //      !OUT     (C),A
RMCF9B:                             //RMCF9B:
                    ;        ;BC = 0x1C00             ;                                  ;                             //      LD      BC,1C00h
                    ;        ;DE = 0x072F             ;                                  ;                             //      LD      DE,072Fh
                    ;        ;IO[BC] = D            ;                                  ;                             //      !OUT     (C),D
a = B - 1           ;f=a&0xff;B = a                 ;F.Z=((a&0xff)==0)  ;              ;                             //      DEC     B
                    ;        ;IO[BC] = E            ;                                  ;                             //      !OUT     (C),E
a = B + 1           ;f=a&0xff;B = a                 ;F.Z=((a&0xff)==0)  ;              ;                             //      INC     B
                    ;        ;DE = 0x0931             ;                                  ;                             //      LD      DE,0931h
                    ;        ;IO[BC] = D            ;                                  ;                             //      !OUT     (C),D
a = B - 1           ;f=a&0xff;B = a                 ;F.Z=((a&0xff)==0)  ;              ;                             //      DEC     B
                    ;        ;IO[BC] = E            ;                                  ;                             //      !OUT     (C),E
a = B + 1           ;f=a&0xff;B = a                 ;F.Z=((a&0xff)==0)  ;              ;                             //      INC     B
                    ;        ;DE = 0x0C80             ;                                  ;                             //      LD      DE,0C80h
                    ;        ;IO[BC] = D            ;                                  ;                             //      !OUT     (C),D
a = B - 1           ;f=a&0xff;B = a                 ;F.Z=((a&0xff)==0)  ;              ;                             //      DEC     B
                    ;        ;IO[BC] = E            ;                                  ;                             //      !OUT     (C),E
a = B + 1           ;f=a&0xff;B = a                 ;F.Z=((a&0xff)==0)  ;              ;                             //      INC     B
                    ;        ;DE = 0x0D03             ;                                  ;                             //      LD      DE,0D03h
                    ;        ;IO[BC] = D            ;                                  ;                             //      !OUT     (C),D
a = B - 1           ;f=a&0xff;B = a                 ;F.Z=((a&0xff)==0)  ;              ;                             //      DEC     B
                    ;        ;IO[BC] = E            ;                                  ;                             //      !OUT     (C),E
                    ;        ;A = 0x00              ;                                  ;                             //      LD      A,00h
                    ;        ;GOS(*(sp++) = (int)&&CFC3;goto RMCBCD;CFC3:a=a;)               ;                             //      CALL    RMCBCD
                    ;        ;GOS(*(sp++) = (int)&&CFC6;goto RMCCB9;CFC6:a=a;)               ;                             //      CALL    RMCCB9
                    ;        ;GOS(*(sp++) = (int)&&CFC9;goto RMCA90;CFC9:a=a;)               ;                             //      CALL    RMCA90
//      POP     DE                             ////      POP     DE
sp--;cnt_sp--;                             ////c:sp--;cnt_sp--;
                    ;        ;RET(goto **(--sp);)         ;                                  ;                             //      RET
