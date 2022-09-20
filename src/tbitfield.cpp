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
    pMem = new TELEM[len];
    MemLen = len;
    BitLen = len * sizeof(TELEM);
    for (int i = 0; i < len; i++) 
        pMem[i] = 0;

}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
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
    const int index = n / sizeof(TELEM);
    return index;
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
    return pMem[GetMemIndex(n)];
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{

    return MemLen*sizeof(TELEM);
}

void TBitField::SetBit(const int n) // установить бит
{
    
    pMem[GetMemIndex(n)] = GetMemMask(n) | (1 << n);
}

void TBitField::ClrBit(const int n) // очистить бит
{
    pMem[GetMemIndex(n)] = GetMemMask(n) & ~(1 << n);
}

int TBitField::GetBit(const int n) const // получить значение бита
{   
    
    TELEM buf = GetMemMask(n) & (1 << n);
    buf >> (n % sizeof(TELEM));
    return buf ;
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
    MemLen = bf.MemLen;
    BitLen = bf.BitLen;
    pMem = new TELEM[MemLen];
    for (int i = 0; i < MemLen; i++)
        pMem[i] = bf.pMem[i];

    return (*this) ;
}

bool TBitField::operator==(const TBitField &bf) const // сравнение
{
    if (this->MemLen == bf.MemLen) {
        
    }
    else
    {   
        return false
    }
  return ;
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
  return FAKE_INT;
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
    return FAKE_BITFIELD;
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
    return FAKE_BITFIELD;
}

TBitField TBitField::operator~(void) // отрицание
{
    return FAKE_BITFIELD;
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
    return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
    return ostr;
}
