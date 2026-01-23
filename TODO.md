# TODO PARSING MAP - cub3D

## 📋 FASE 7: Validazione mappa

### Check 1: Dimensioni e forma
- [x] Verifica che mappa sia almeno 3x3

### Check 2: Caratteri validi
- [x] Verifica che mappa contenga solo: '0', '1', 'N', 'S', 'E', 'W', ' '
- [x] Trova e salva posizione del player
- [x] Conta i player (deve essere esattamente 1)

### Check 3: Mappa chiusa
- [x] Usa algoritmo floodfill per verificare che non ci siano "buchi"
- [x] Deve partire dalla posizione del player
- [x] Se raggiunge un bordo con ' ' → mappa aperta (error)

---

## ✅ CHECKLIST FINALE

- [x] File .cub viene letto correttamente
- [x] Tutti e 6 gli identifiers sono estratti
- [x] Path textures sono salvati in array
- [x] Colori floor e ceiling sono convertiti in int RGB
- [x] Matrice mappa è allocata con dimensioni corrette
- [x] Matrice è popolata con padding quando necessario
- [x] Tutte le righe hanno stessa lunghezza
- [x] Mappa contiene esattamente 1 player
- [x] Mappa contiene solo caratteri validi
- [x] Mappa è chiusa (floodfill non trova buchi)
- [x] Posizione e orientamento player sono salvati
- [x] Nessun memory leak (test con valgrind)
- [x] Gestione errori con cleanup appropriato

## Da sistemare
Error ❌
Issues with map: maze leak. --- con righe vuote in mezzo, con spazi vuoti in mezzo. Apre window comunque --> fixed
Issues with map: tab --> fixed
glide: vettore x-y calcola prima x o y, se puoi andarci aggiorni prima uno o l'altro. es: x rimane fissa, si muove su y -> glida
- leaks with esc button and x
