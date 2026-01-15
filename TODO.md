# TODO PARSING MAP - cub3D

**Flow generale:**
1. Leggi file e salva ogni riga map in un nodo della lista ✅
2. Conta nodi (= numero righe) e trova riga più lunga (= numero colonne) ✅
3. Alloca matrice con dimensioni corrette ✅
4. Copia contenuto lista nella matrice (con padding se necessario) ✅
5. Free della lista temporanea ✅
6. Valida la matrice ✅

## 📋 FASE 7: Validazione mappa

### Check 1: Dimensioni e forma
- Verifica che mappa sia almeno 3x3
- Verifica che tutte le righe abbiano effettivamente stessa lunghezza

### Check 2: Caratteri validi
- Verifica che mappa contenga solo: '0', '1', 'N', 'S', 'E', 'W', ' '
- Trova e salva posizione del player
- Conta i player (deve essere esattamente 1)

### Check 3: Mappa chiusa
- Usa algoritmo floodfill per verificare che non ci siano "buchi"
- Deve partire dalla posizione del player
- Visita tutti gli '0' raggiungibili
- Se raggiunge un bordo con ' ' → mappa aperta (error)

---

## ✅ CHECKLIST FINALE

- [ ] File .cub viene letto correttamente
- [ ] Tutti e 6 gli identifiers sono estratti
- [ ] Path textures sono salvati in array
- [ ] Colori floor e ceiling sono convertiti in int RGB
- [ ] Matrice mappa è allocata con dimensioni corrette
- [ ] Matrice è popolata con padding quando necessario
- [ ] Tutte le righe hanno stessa lunghezza
- [ ] Mappa contiene esattamente 1 player
- [ ] Mappa contiene solo caratteri validi
- [ ] Mappa è chiusa (floodfill non trova buchi)
- [ ] Posizione e orientamento player sono salvati
- [ ] Nessun memory leak (test con valgrind)
- [ ] Gestione errori con cleanup appropriato

## Da sistemare
Error - player count -> segfault con mappa incompleta


