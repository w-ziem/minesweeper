# minesweeper



I: 
- w zależności od argumentów wywołania (getopt) generowanie planszy (stuktury pól, planszy, generowanie min, ustawianie flag, odkrwyanie pola)
- wyświetlanie planszy
- aktualny winik gracz... (UI gry)
- zapisywanie i przechowywanie gdzies wynikow a na koniec wyswietlanie
- wczytywanie gracza przed rozpoczeciem

II:
- logika gry: wczytywanie ruchu z stdin, co sie dzieje po ruchu w zależności od tego na co trafił (odkrywanie) [game.c]
- sprawdzanie i wyswietlanie wyniku 
- wczytywanie gry z pliku



16.01 16.00: 
1. zakładam, że będą działać takie funkcje: 
reveal_square()
place_flag()
reveal_adjacent_squares()
display_board()
reveal_all_mines()
2. zakładam, że będzie coś typu stuct board_t, która przechowuje jako 2d lista struct field, które ma (row, col, isMine, isFlag, isRevealed, adjacentMines) - może być inaczej ofc
3. nazwy funkcji są z podłogami, nazwy zmiennych są camelCasem