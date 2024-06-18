# esercizio 0

Questa libreria si occuppa di implementare le strutture astratte, che quindi non possono essere istanziate dall’utente e che definiscono il livello alto della gerachia.

### Container

La struttura più generica in assoluto. Ha solo un attributo size che indica la dimensione.

- Empty()

```cpp
virtual bool Empty() const noexcept { return size == 0; }
```

- Size()

```cpp
virtual ulong Size() const noexcept { return size; }
```

---

### ClearableContainer : public Container

Contenitori con la possibilità di essere svuotati.

- Clear()

```cpp
virtual void Clear() { size = 0; }
```

---

### ResizibleContainer : public ClearableContainer

Contenitori che possono anche essere ridimensionati.

- Resize()

```cpp
virtual void Resize(ulong newSize) { size = newSize; }
```

---

### TestableContainer : public Container

Contenitori con la possibilità di verificare l’esistenza di un dato all’interno della struttura.

- Exists()

```cpp
virtual bool Exists(const Data&) const noexcept = 0;
```

---

### TraversableContainer : public TestableContainer

Questa famiglia di contenitori possono essere visitati attraverso una funzione apposita, in diversi ordini possibili.

- Traverse()

```cpp
using TraverseFun = std::function<void(const Data&)>;
virtual void Traverse(TraverseFun) const = 0;
```

In realtà all’interno del file sono presenti altre classi che si occupano della visita in un determinato ordine (Pre, Post, In, Breadth).

---

### MappableContainer : public TraversableContainer

Identica alla classe Traversable permette in più di manipolare i dati, che quindi non saranno costanti: in altre parole potranno essere passate funzioni che possono alterare i valori dei dati, ma anche banalmente rimuoverli dalla struttura.

- Map()

```cpp
using MapFun = std::function<void(Data&)>;
virtual void Map(MapFun) = 0;
```

---

### LinearContainer : public Pre/Post-OrderMappableContainer

Contenitori i cui dati sono ordinati linearmente e che possono quindi avere un indice. Nel file di Linear è presente anche la classe SortableLinearContainer che estende LinearContainer e contiene in più una funzione Sort() implementata come QuickSort().

- Front()

```cpp
Data& Front() {

    if (size != 0) return operator[](0);
    else throw std::length_error("trying acess to an empty container.");
}
```

- Back()

```cpp
Data& Back() {

    if (size != 0) return operator[](size - 1);
    else throw std::length_error("trying acess to an empty container.");
}
```

- Traverse() (override)

```cpp
inline void Traverse(TraverseFun fun) const {
    
    for (ulong i = 0; i < size; i++) { fun(operator[](i)); }
}
```

---

### DictionaryContainer : public TestableContainer

Un dizionario è un tipo di struttura su cui possono essere effettuate solo 3 operazioni: inserimento, cancellazione e ricerca. Tutte le funzioni per inserimenti e cancellazioni hanno come tipo di ritorno un valore booleano per verificare se dati sono stati correttamente inseriti/rimossi o meno.

- Insert()

```cpp
virtual bool Insert(Data&&) = 0;
```

- Remove()

```cpp
virtual bool Remove(const Data&) = 0;
```

- InsertAll()

```cpp
inline bool InsertAll(MappableContainer<Data>&& cntr) {

    bool allInserted = true;
    cntr.Map([this, &allInserted](Data& d) { allInserted &= Insert(std::move(d)); });
    return allInserted;
}
```

- RemoveAll()

```cpp
inline bool RemoveAll(const TraversableContainer<Data>& cntr) {

    bool allRemoved = true;
    cntr.Traverse([this, &allRemoved](const Data& d) { allRemoved &= Remove(d); });
    return allRemoved;
}
```