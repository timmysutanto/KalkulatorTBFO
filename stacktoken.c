// Nama/NIM  : Kevin Nathaniel Wijaya/13517072
// Tanggal   : 17 Oktober 2018
// Topik     : Pra Praktikum 07
// Nama file : stackt.c
// Deskripsi : File Body ADT Stack Statik

/* deklarasi stack yang diimplementasi dengan tabel kontigu dan ukuran sama */
/* TOP adalah alamat elemen puncak */
/* Implementasi dalam bahasa C dengan alokasi statik */

#include "boolean.h"
#include "stacktoken.h"

/* ************ Prototype ************ */
/* *** Konstruktor/Kreator *** */
void CreateEmptyST(StackToken *S);
/* I.S. sembarang; */
/* F.S. Membuat sebuah stack S yang kosong berkapasitas MaxEl */
/* jadi indeksnya antara 1.. MaxEl+1 karena 0 tidak dipakai */
/* Ciri stack kosong : TOP bernilai Nil */
{
	Top(*S) = NilToken;
}

/* ************ Predikat Untuk test keadaan KOLEKSI ************ */
boolean IsEmptyST (StackToken S)
/* Mengirim true jika Stack kosong: lihat definisi di atas */
{
	return (Top(S) == NilToken);
}

boolean IsFullST (StackToken S)
/* Mengirim true jika tabel penampung nilai elemen stack penuh */
{
	return (Top(S) == MaxElToken);
}

/* ************ Menambahkan sebuah elemen ke Stack ************ */
void PushST (StackToken * S, Token X)
/* Menambahkan X sebagai elemen Stack S. */
/* I.S. S mungkin kosong, tabel penampung elemen stack TIDAK penuh */
/* F.S. X menjadi TOP yang baru,TOP bertambah 1 */
{
	Top(*S)++;
	InfoTop(*S) = X;
}

/* ************ Menghapus sebuah elemen Stack ************ */
void PopST (StackToken * S, Token* X)
/* Menghapus X dari Stack S. */
/* I.S. S  tidak mungkin kosong */
/* F.S. X adalah nilai elemen TOP yang lama, TOP berkurang 1 */
{
	*X = InfoTop(*S);
	Top(*S)--;
}
