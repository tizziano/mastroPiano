v 20130925 2
C 45500 40000 1 0 1 connector8-1.sym
{
T 45400 43200 5 10 0 0 0 6 1
device=CONNECTOR_8
T 45400 42600 5 10 1 1 0 6 1
refdes=CONNB-colonne
}
C 45500 43200 1 0 1 connector8-1.sym
{
T 45400 46400 5 10 0 0 0 6 1
device=CONNECTOR_8
T 45400 45800 5 10 1 1 0 6 1
refdes=CONNA-righe
}
N 41100 42100 41100 40200 4
N 41100 40200 43800 40200 4
N 40100 42300 41300 42300 4
N 41300 42300 41300 40500 4
N 41300 40500 43800 40500 4
N 43800 40800 41500 40800 4
N 41500 40800 41500 42500 4
N 40100 42500 41500 42500 4
N 43800 41100 41700 41100 4
N 41700 41100 41700 42700 4
N 40100 42700 41700 42700 4
N 43800 41400 41900 41400 4
N 41900 41400 41900 42900 4
N 40100 42900 41900 42900 4
N 43800 41700 42100 41700 4
N 42100 41700 42100 43100 4
N 40100 43100 42100 43100 4
N 43800 42000 42300 42000 4
N 42300 42000 42300 43300 4
N 40100 43300 42300 43300 4
N 43800 42300 42500 42300 4
N 42500 42300 42500 43500 4
N 40100 43500 42500 43500 4
N 40100 43700 42700 43700 4
N 42700 43700 42700 43400 4
N 42700 43400 43800 43400 4
N 40100 43900 42900 43900 4
N 42900 43900 42900 43700 4
N 42900 43700 43800 43700 4
N 43800 44000 43100 44000 4
N 40100 44100 43100 44100 4
N 43100 44100 43100 44000 4
N 40100 44300 43800 44300 4
N 43300 45500 43800 45500 4
N 43000 45200 43800 45200 4
N 42700 44900 43800 44900 4
N 42400 44600 43800 44600 4
N 45600 42300 48200 42300 4
N 45600 42000 48600 42000 4
N 45600 41700 49000 41700 4
N 45600 41400 49400 41400 4
N 45600 41100 49800 41100 4
N 45600 40800 50200 40800 4
N 45600 40500 50600 40500 4
N 45600 40200 51000 40200 4
N 45600 45500 51400 45500 4
N 48200 42300 48200 45800 4
N 48600 42000 48600 45800 4
N 49000 41700 49000 45800 4
N 49400 41400 49400 45800 4
N 49800 41100 49800 45800 4
N 50200 40800 50200 45800 4
N 50600 40500 50600 45800 4
N 51000 40200 51000 45800 4
N 45600 45200 51400 45200 4
N 45600 44900 51400 44900 4
N 45600 44600 51400 44600 4
N 45600 44300 51400 44300 4
N 45600 44000 51400 44000 4
N 45600 43700 51400 43700 4
N 45600 43400 51400 43400 4
C 49500 47700 1 0 0 diode-1.sym
{
T 49900 48300 5 10 0 0 0 0 1
device=DIODE
T 50100 48300 5 10 1 1 180 0 1
refdes=Dij
}
C 49500 46900 1 90 0 switch-pushbutton-no-1.sym
{
T 49200 47500 5 10 1 1 180 0 1
refdes=Sij
T 48900 47300 5 10 0 0 90 0 1
device=SWITCH_PUSHBUTTON_NO
}
N 48800 46900 50700 46900 4
N 50400 48500 50400 46600 4
C 51100 46400 1 90 0 cerchio.sym
C 37600 41100 1 0 0 arduino-1.sym
{
T 39700 46695 5 10 1 1 0 0 1
refdes=Arduino Uno-R3
T 37600 41095 5 10 0 1 0 0 1
footprint=ARDUINO_UNO
T 37600 41095 5 10 0 1 0 0 1
device=ARDUINO_UNO
}
N 43300 45500 43300 46100 4
N 43300 46100 40100 46100 4
N 43000 45200 43000 45900 4
N 43000 45900 40100 45900 4
N 42700 44900 42700 45700 4
N 42700 45700 40100 45700 4
N 42400 44600 42400 45500 4
N 42400 45500 40100 45500 4
N 41100 42100 40100 42100 4
T 45500 38500 9 10 1 0 0 0 2
Mastropiano prototipo 1
banco di prova
C 42600 46600 1 0 0 digitalIn.sym
C 42200 46100 1 0 0 cerchio.sym
C 41800 37600 1 0 0 cerchio.sym
C 42200 38400 1 0 0 digitalOut.sym
