# TODO PARSING MAP - cub3D

**Flow generale:**
1. Leggi file e salva ogni riga map in un nodo della lista ✅
2. Conta nodi (= numero righe) e trova riga più lunga (= numero colonne) ✅
3. Alloca matrice con dimensioni corrette ✅
4. Copia contenuto lista nella matrice (con padding se necessario) ✅
5. Free della lista temporanea ✅
6. Valida la matrice


**Valida la matrice**
La validazione della matrice è la fase in cui verifichi che la mappa sia effettivamente "giocabile" secondo le regole di cub3D. Il fatto che tu l'abbia copiata in una matrice non significa che sia corretta.

Ecco i controlli fondamentali che devi fare al punto 6:

1. Caratteri Permessi
Devi scorrere tutta la matrice e assicurarti che ogni carattere sia uno di questi:

1 (Muro)

0 (Pavimento)

N, S, E, W (Posizione iniziale del player)

(Spazio vuoto/Padding)

2. Controllo del Player
Presenza: Deve esserci almeno una posizione di partenza (N, S, E o W).

Unicità: Non possono esserci due o più player. Se ne trovi un secondo, devi dare errore.

3. Mappa Chiusa (Il controllo più difficile)
La mappa deve essere completamente circondata da muri (1). Qualsiasi 0 o posizione del player non deve mai "toccare" l'esterno o uno spazio vuoto.

Ci sono due modi comuni per farlo:

A. Il controllo dei vicini (Semplice)
Per ogni 0 o Player nella matrice:

Controlla sopra, sotto, a destra e a sinistra.

Se un vicino è uno spazio vuoto ( ) o è fuori dai bordi della matrice, la mappa è aperta -> ERRORE.

B. Flood Fill (Robusto)
È l'algoritmo che usa il secchiello di Paint:

Parti dalla posizione del player.

Ti espandi ricorsivamente su tutti gli 0 adiacenti.

Se durante l'espansione tocchi il bordo della matrice o uno spazio vuoto, significa che l'aria "scappa" e la mappa è aperta.

---

## 📋 FASE 1: Struttura dati

### Creare struttura nodo per lista
- Ogni nodo contiene una stringa (una riga della mappa)
- Ogni nodo punta al successivo
- Aggiungere typedef in `cub3d.h`

---

## 📋 FASE 2: Funzioni helper per lista

**Da libft:**
- ✅ `ft_lstnew()` - crea nodo
- ✅ `ft_lstadd_back()` - aggiungi nodo in coda
- ✅ `ft_lstsize()` - conta nodi
- ✅ `ft_lstclear()` - free lista

**Da so_long puoi riusare/adattare:**

### 1. Funzione `add_line()` (da map_parser.c)
- Crea nodo con `ft_lstnew()`
- Aggiunge alla lista con `ft_lstadd_back()`
- Ritorna 1 se success, 0 se fail

### 2. Funzione `read_map()` (da map_parser.c)

### 3. Funzione `count_valid_rows()` (da map_to_matrix.c)

### 4. Funzione `populate_matrix()` (da map_to_matrix.c)

- **PADDING**: se riga è più corta di `max_cols`, riempire con spazi

### Funzione da scrivere: trova lunghezza massima
- Scorri tutti i nodi della lista
- Per ogni nodo calcola lunghezza stringa (dopo trim di `\n`)
- Tieni traccia della lunghezza massima trovata
- Ritorna lunghezza massima (sarà `cols`)

---

## 📋 FASE 3: Leggere mappa in lista

1. Dichiarare variabili:
   - Puntatore head lista (inizialmente NULL)
   - Flag booleano `map_started` (inizialmente false)
   - Contatore identifiers letti

2. Loop principale con `get_next_line()`:
   - Se linea vuota → skip e continua
   - Se è identifier E non abbiamo ancora letto 6 identifier:
     - Chiamare `read_ids()`
     - Incrementare contatore
   - Se è riga mappa (inizia con '1' dopo eventuali spazi):
     - Creare nodo con questa riga
     - Aggiungerlo alla lista
     - Settare `map_started = true`
   - Se `map_started` è true E trovi riga che non è mappa:
     - **ERROR**: la mappa deve essere l'ultimo elemento del file
     - Cleanup e exit

3. Alla fine del loop:
   - Hai una lista con tutte le righe della mappa
   - Chiudere file descriptor

---

## 📋 FASE 4: Calcolare dimensioni

1. Chiamare funzione conta-nodi → numero righe
2. Chiamare funzione trova-lunghezza-massima → numero colonne
3. Salvare questi valori (serviranno per allocazione)

---

## 📋 FASE 5: Convertire lista → matrice

1. Allocare array di puntatori per `rows + 1` (NULL terminated)

2. Per ogni nodo della lista:
   - Allocare spazio per stringa di lunghezza `max_cols + 1`
   - Usare `ft_strtrim()` per rimuovere `\n` dalla riga
   - Copiare contenuto nodo nella riga della matrice
   - Se riga originale è più corta di max_cols:
     - Fare padding riempiendo con spazi ' '
   - Tutti gli spazi alla fine devono diventare ' ' per far funzionare i check

3. Ultima riga = NULL (matrice NULL-terminated)

4. Ritornare la matrice

---

## 📋 FASE 6: Salvare dati in t_data

1. Assegnare matrice creata a `data->map->grid`
2. Salvare numero righe in `data->map->rows`
3. Salvare numero colonne in `data->map->cols`
4. Liberare lista temporanea (non serve più)

---

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

