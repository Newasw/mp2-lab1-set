// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tset.cpp - Copyright (c) Гергель В.П. 04.10.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Множество - реализация через битовые поля

#include "tset.h"
TSet::TSet(int mp) : BitField(mp)
{
    this->MaxPower = mp;

}

// конструктор копирования
TSet::TSet(const TSet& s) : BitField(this->MaxPower / sizeof(TELEM))
{
    this->MaxPower = s.MaxPower;
    this->BitField = s.BitField;

}

// конструктор преобразования типа
TSet::TSet(const TBitField& bf) : BitField(bf.GetLength() / sizeof(TELEM))
{
    this->MaxPower = bf.GetLength();
    this->BitField = bf;
}

TSet::operator TBitField()
{
    TBitField res(this->MaxPower / sizeof(TELEM));
    res = this->BitField;
    return res;
}

int TSet::GetMaxPower(void) const // получить макс. к-во эл-тов
{

    return this->MaxPower;
}

int TSet::IsMember(const int Elem) const // элемент множества?
{
    if (Elem > -1) {
        return this->BitField.GetBit(Elem);
    }
    else {
        throw "ERROR ";
    }

}

void TSet::InsElem(const int Elem) // включение элемента множества
{
    this->BitField.SetBit(Elem);
}

void TSet::DelElem(const int Elem) // исключение элемента множества
{
    this->BitField.ClrBit(Elem);
}

// теоретико-множественные операции

TSet& TSet::operator=(const TSet& s) // присваивание
{
    this->MaxPower = s.MaxPower;
    this->BitField = s.BitField;
    return *this;
}

int TSet::operator==(const TSet& s) const // сравнение
{
    if (this->MaxPower == s.MaxPower) {
        if (this->BitField == s.BitField) {
            return 1;
        }
        else {
            return 0;
        }
    }
    else {
        throw "ERROR";
    }
}

int TSet::operator!=(const TSet& s) const // сравнение
{
    return (!(this == &s));
}

TSet TSet::operator+(const TSet& s) // объединение
{
    if (this->MaxPower >= s.MaxPower) {
        TSet res(this->MaxPower);
        res.BitField = this->BitField | s.BitField;
        return res.BitField;
    }
    else {
        TSet res(s.MaxPower);
        res.BitField = this->BitField | s.BitField;
        return res.BitField;
    }

}

TSet TSet::operator+(const int Elem) // объединение с элементом
{
    if (Elem > this->MaxPower) {
        throw "ERROR";
    }
    else {
        TSet res(this->MaxPower);
        res.InsElem(Elem);

        return (res + (*this));
    }
}

TSet TSet::operator-(const int Elem) // разность с элементом
{
    this->DelElem(Elem);
    return *this;
}

TSet TSet::operator*(const TSet& s) // пересечение
{
    if (this->MaxPower >= s.MaxPower) {
        TSet res(this->MaxPower);
        res.BitField = this->BitField & s.BitField;
        return res.BitField;
    }
    else {
        TSet res(s.MaxPower);
        res.BitField = this->BitField & s.BitField;
        return res.BitField;
    }
}

TSet TSet::operator~(void) // дополнение
{
    TSet res(this->MaxPower);
    res.BitField = ~(this->BitField);
    return res.BitField;
}

// перегрузка ввода/вывода

istream& operator>>(istream& istr, TSet& s) // ввод
{
    return istr;
}

ostream& operator<<(ostream& ostr, const TSet& s) // вывод
{
    return ostr;
}
