// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"

// Fake variables used as placeholders in tests
static const int FAKE_INT = -1;
static TBitField FAKE_BITFIELD(1);

TBitField::TBitField(int len)
{
    if (len < 0) {
        cout << "len < 0 =(((";
        throw "ERROR : lenght is negative";
    }
    pMem = new TELEM[len];
    MemLen = len;
    BitLen = len * sizeof(TELEM);
    for (int i = 0; i < len; i++)
        pMem[i] = 0;

}

TBitField::TBitField(const TBitField& bf) // конструктор копирования
{
    MemLen = bf.MemLen;
    BitLen = bf.BitLen;
    pMem = new TELEM[MemLen];
    for (int i = 0; i < MemLen; i++)
        pMem[i] = bf.pMem[i];

}

TBitField::~TBitField()
{
    delete[] pMem;
    pMem = nullptr;
}

int TBitField::GetMemIndex(const int n) const // индекс в пямяти для бита n
{
    return (n / sizeof(TELEM));
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
    return pMem[GetMemIndex(n)];
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{

    return MemLen;
}

void TBitField::SetBit(const int n) // установить бит
{
    if (n < 0 || n > MemLen) {
        throw "ERROR invalid index";
    }
    else { pMem[GetMemIndex(n)] = GetMemMask(n) | (1 << (n % (sizeof(TELEM) * 8))); }
}

void TBitField::ClrBit(const int n) // очистить бит
{
    if (n < 0 || n > MemLen) {
        throw "ERROR invalid index";
    }
    else { pMem[GetMemIndex(n)] = GetMemMask(n) & ~(1 << (n % (sizeof(TELEM) * 8))); }
}

int TBitField::GetBit(const int n) const // получить значение бита
{
    if (n < 0 || n > MemLen) {
        throw "ERROR invalid index";
    }

    else {
        if ((GetMemMask(n) & (1 << (n % (sizeof(TELEM) * 8)))) == 0) {
            return 0;
        }
        else {
            return 1;
        }
    }
}

// битовые операции

TBitField& TBitField::operator=(const TBitField& bf) // присваивание
{
    MemLen = bf.MemLen;
    BitLen = bf.BitLen;
    delete[] this->pMem;
    pMem = new TELEM[MemLen];
    for (int i = 0; i < MemLen; i++)
        pMem[i] = bf.pMem[i];

    return (*this);
}

int TBitField::operator==(const TBitField& bf) const // сравнение
{
    if (this->MemLen == bf.MemLen) {
        for (int i = 0; i < bf.MemLen; i++) {
            if (this->pMem[i] != bf.pMem[i]) {
                return 0;
            }
        }
        return 1;
    }
    else {
        cout << "incomparable" << endl;
        return 0;
    }
}

int TBitField::operator!=(const TBitField& bf) const // сравнение
{
    return (!(this == &bf));
}

TBitField TBitField::operator|(const TBitField& bf) // операция "или"
{
    if (this->MemLen >= bf.MemLen) {
        TBitField res(this->MemLen);
        for (int i = 0; i < bf.MemLen; i++) {
            res.pMem[i] = (this->pMem[i]) | (bf.pMem[i]);
        }
        for (int i = bf.MemLen; i < this->MemLen - bf.MemLen; i++) {
            res.pMem[i] = this->pMem[i];
        }
        return res;
    }
    else {
        TBitField res(bf.MemLen);
        for (int i = 0; i < this->MemLen; i++) {
            res.pMem[i] = (this->pMem[i]) | (bf.pMem[i]);
        }
        for (int i = this->MemLen; i < bf.MemLen - this->MemLen; i++) {
            res.pMem[i] = bf.pMem[i];
        }
        return res;

    }
}

TBitField TBitField::operator&(const TBitField& bf) // операция "и"
{
    if (this->MemLen <= bf.MemLen) {
        TBitField res(bf.MemLen);
        for (int i = 0; i < bf.MemLen; i++) {
            res.pMem[i] = (this->pMem[i]) & (bf.pMem[i]);
        }
        return res;
    }
    else {
        TBitField res(this->MemLen);
        for (int i = 0; i < this->MemLen; i++) {
            res.pMem[i] = (this->pMem[i]) & (bf.pMem[i]);
        }
        return res;

    }
}

TBitField TBitField::operator~(void) // отрицание
{
    TBitField res(this->MemLen);
    for (int i = 0; i < res.MemLen; i++) {
        if (this->GetBit(i) == 0) {
            res.SetBit(i);
        }
    }
    return res;
}

// ввод/вывод

istream& operator>>(istream& istr, TBitField& bf) // ввод
{
    int n = 0;
    istr >> n;
    bf.SetBit(n);




    return istr;
}

ostream& operator<<(ostream& ostr, const TBitField& bf) // вывод
{
    int n = 0;
    int bit = 0;
    while (n < bf.BitLen) {
        bit = bf.GetBit(n);
        ostr << bit;
        n++;

    }
    return ostr;
}
