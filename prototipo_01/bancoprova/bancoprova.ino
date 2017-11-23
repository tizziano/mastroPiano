/*
 * kbd_controller.ino
 * 
 * Copyright 2016 tiziano <tiziano.detogni@gmail.com>
 * 
 * Controller matrice 8x8 della tastiera viscount
 * 
 * Versione 1: arduino UNO R3, banco di prova scansione tastiera
 * 
 * Possibilità:
 *    usa tutti i pin disponbili di arduino
 *      impiega se possibile due porte da 8 bit...
 *        impossibile. PB0..5=6, PD2..7=6, PC0..3=4, totale 18 pin
 *        potresti farlo, ma con un arduino Mega (PortA0-7 e PortC0-7)
 * 
 * siamo abbastanza veloci?
 * sarebbe opportuno usare un'interrupt?
 * 
 * Is a scanning frequency of 1000Hz too low? 
 * I've heard somewhere commercial keyboard use 2000Hz. 
 * Perhaps someone can measure one with a scope?
 * 
 * Per misurare la frequenza di scansione della tastiera, sarebbe opportuno 
 * chiarire quale periodo si intende con questo termine.  
 * todo:  misura millisecondi tra una scansione e la successiva
 * 
 * 
 * todo:
 *    elimina i cicli for nel loop
 * 
 *    midinote=12*col+36*row=12*(col+3*row)
 *    ma dovresti incrementare un contatore durante la scansione in modo
 *    da evitare queste moltiplicazioni che rallentano le cose.   ok
 * 
 *    prove antirimbalzo???
 * 
 *    esegui il debug sulla seriale
 * 
 *    todo: 
 *      rilevazione velocità dei tasti? è un altro progetto
 *    
 */
#define DEBUGSERIAL
#define KBDOFFSET 36    // offset DO-2
#define TESTBOUNCEno

uint8_t colpins[]={6,7,8,9,10,11,12,13};  // connettore viscount colonne matrice
uint8_t rowpins[]={2,3,4,5,A0,A1,A2,A3};  // connettore viscount righe matrice
 
boolean keyPressed[64];
int noteVelocity = 100;     // se non rilevi la velocità devi usare questo valore predefinito 
 
void noteOn(int cmd, int pitch, int velocity) {

    #ifdef DEBUGSERIAL
      String s="noteon:";
      Serial.println(s+cmd+" "+pitch+" "+velocity);
    #else
      // todo: MIDI out
//~       Serial.write(cmd);
//~       Serial.write(pitch);
//~       Serial.write(velocity);
    #endif
}

void scankeyboard() {
  static uint8_t scanrow=0;
  static uint8_t scancol=0;
  static uint8_t midinote=KBDOFFSET;  

  // attiva la colonna (scancol)
  digitalWrite(colpins[scancol], LOW);

  int xrow=digitalRead(rowpins[scanrow]);
  //todo: controllo antirimbalzo?
  
  // noteon
  if ( !xrow && !keyPressed[scancol+(scanrow*8)] ) {
    keyPressed[scancol+(scanrow*8)]=true;
    noteOn(0x90, midinote, noteVelocity);
  }
  
  //noteoff
  if ( xrow && keyPressed[scancol+(scanrow*8)] ) {
    keyPressed[scancol+(scanrow*8)]=false;
    noteOn(0x80, midinote, 0);
  }

  digitalWrite(colpins[scancol], HIGH);

  midinote++;
  if (++scanrow==8) {
     scanrow=0;
     if (++scancol==8) {
        scancol=0;
        midinote=KBDOFFSET;   // offset DO-2
      } //else midinote+=8;
  }
}
 
void setup() {

    // azzeramento array keyPressed
    for(int i = 0; i < 64; i++){
      keyPressed[i]=false;
    }

    // configurazione pin in uscita, pin in ingresso e pullup interno 
    for(int i = 0; i < 8; i++){
      pinMode(colpins[i],OUTPUT);
      pinMode(rowpins[i],INPUT_PULLUP);
    };
 
    #ifdef DEBUGSERIAL
      // 300, 600, 1200, 2400, 4800, 9600, 14400, 19200, 28800, 38400, 57600, or 115200
      // 14400 e 28800 non vanno!
      Serial.begin(57600);
      Serial.println("debug keyscan startup");
    #else
      // todo: MIDI output
//~       Serial.begin(31250);    // velocità secondo lo standard MIDI
//~                               // la seriale lavora come MIDI OUT
    #endif
}

void loop() {
  scankeyboard(); 
//~   delay(500);
}
