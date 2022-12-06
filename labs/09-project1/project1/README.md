
# Časovač s LCD rozhraním <br> založený na kontroléry ATMEGA328p 

### Členovia týmu

**Dominik Caban** <br>
- užívateľské rozrhanie (display, joistick), návrh shieldu, finálna dokumentácia (Text, Schéma zapojenia, Strih videa)

**Ivo Dovičák** <br>
- užívateľské rozrhanie (display, encoder, flowchart), preslov u videa 

### Obsah

* [Ciele projektu](#objectives)
* [Popis Hardwaru](#hardware)
* [Popis Software](#software)
* [Video](#video)
* [Referencie](#references)

<a name="objectives"></a>

## Ciele projektu
- vytvoriť časovač s užívateľským tozhraním,
- využiť analógový joistick (2 kanály ADC, 1 tlačidlo) a enkóder pre ovládanie užívateľského rozhrania,
- využiť vývojovú dosku Arduino UNO,
- vytvoriť užívateľské rozhranie pomocou LCD modulu Digilent PmodCLP,
- vytvoriť kód a využiť pri tom knižnice vytvorené počas laboratórnych cvičení,
- vytoriť schému a návrh DPS v prostredí Altia (PCB Design Software).

<a name="hardware"></a>

## Popis Hardwaru
### Arduino UNO, Enkóder, Joystick 
V rámci vývojovej sady bola použitá vývojová doska Arduino UNO obsahujúca 14 digitálnych vstupných/výstupných pinov (z ktorých 6 môže byť použitých ako PWM výstupy) a 6 analógových vstupov. Ďalej bol použitý rotačný enkóder typu KY-040, ktorému na jedno 360° otočenie pripadá 20 pulzov. Zároveň bol využitý aj joystick, ktorý sníma v 2 osiach (X a Y) do akej miery je vychýlený (má analógový výstup pre každú z osí). Joystick má aj zabudované tlačidlo (pin SW). Ako posledný bol použitý 16×2 znakový LCD modul (Digilent Pmod CLP), ktorý využíva 8-bitové paralelné dátové rozhranie a umožňuje zobrazovať až 32 rôznych znakov z viac ako 200 možných.

### Shield
- Do nášho študentského projektu sme zakomponovali shield, ktorý by bolo možné umiestniť nad vývojovú dosku Arduino UNO a bolo by tak možné mať hotový finálny produkt bez dodatočných prepojov a kontaktného poľa. Súčasťou shieldu je LCD display, Enkóder, Joistick a Piezoelektrický menič so zabudovaným generátorom. (V simulácii a aj počas laboratórneho cvičenia bol piezoelektrický menič nahradený LED diódou.) 
- Návrh shieldu je realizovaný pomocou aplikácie Altium Designer, viď. obrázky nižšie.


3D Model DPS shieldu <br> (Vrchný pohľad) | 3D Model DPS shieldu <br> (Spodný pohľad)
:-------------------------:|:-------------------------:
![TOP](https://user-images.githubusercontent.com/99599292/206024184-630b0892-5c0f-4bee-af78-f6b76cede5ef.PNG)|![BOT](https://user-images.githubusercontent.com/99599292/206024167-6daa4043-3563-473c-9e71-3126e7d38f11.PNG)

Layoutový pohľad DPS shieldu <br> (Vrchný pohľad) |3D Model DPS shieldu <br> (Bočný pohľad)
:-------------------------:|:-------------------------:
![2D](https://user-images.githubusercontent.com/99599292/206024144-bae264bb-660f-47e1-a58b-0a8ea56003ed.PNG)|![LR_VIEW](https://user-images.githubusercontent.com/99599292/206024231-a2c6670b-b2bc-4459-8b94-76b9149c3647.PNG)

![SchemaTimer](https://user-images.githubusercontent.com/99599292/206024214-85624a24-66cd-4574-841a-bfdcb702cbe3.PNG)
<fig caption> <p align="center"> Schéma DPS shliedu

### Schéma zapojenia modulov 
Funkčnosť zapojenia bola demonštrovaná na základe schémy uvedenej nižšie.
![SchemaZapojenia.PNG](Images/SchemaZapojenia.PNG)
|:--:| 
|*Schéma zapojenia modulov*|

<a name="software"></a>

## Popis Softwaru

### Vývojový diagram
-	INSERT TEXT

![FlowchartV1](https://user-images.githubusercontent.com/99599292/206024249-d700934f-50b6-4252-ad23-c4053fb5dbc2.png)

### Nastavenie časovača
-	INSERT TEXT

|:--:| 
|*Nastavenia časovača*|

### Spustenie časovača
-	INSERT TEXT

|:--:| 
|*Spustenie časovača*|

### Zastavenie časovača
-	INSERT TEXT

|:--:| 
|*Zastavenie časovača*|

## GitHub štruktúra úložiska

   ```c
   ├── include         // Included files
       └── timer.h  
   ├── lib             // Libraries
       └── gpio
           └── gpio.c
           └── gpio.h
       └── lcd
           └── ldc_definitions.h
           └── lcd.h
           └── lcd.c
       └── uart
           └── uart.h
           └── uart.c
   ├── src             // Source file(s)
   │   └── main.c
   ├── test            // No need this
   ├── platformio.ini  // Project Configuration File
   └── README.md       // Report of this project
   ```

## Video 
 INSERT YOUTUBE URL

<a name="references"></a>

## Referencie

1. ATMEGA 328p Datasheet: 
- https://ww1.microchip.com/downloads/en/DeviceDoc/Atmel-7810-Automotive-Microcontrollers-ATmega328P_Datasheet.pdf

2. Arduino UNO R3 Reference Manual: 
- https://docs.arduino.cc/hardware/uno-rev3

3. Pmod CLP Reference Manual: 
- https://digilent.com/reference/pmod/pmodclp/start

4. Rotary Encoder Overview: 
- https://howtomechatronics.com/tutorials/arduino/rotary-encoder-works-use-arduino/

5. Github:
- https://github.com/tomas-fryza/digital-electronics-2
 
6. Výsledné návrhové podklady + Gerbery:
- https://1drv.ms/u/s!ApTT7Dyt-1k9hZRq7iB1lt6IxRTp-Q?e=aoRU1v

