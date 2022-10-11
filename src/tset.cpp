// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tset.cpp - Copyright (c) Гергель В.П. 04.10.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Множество - реализация через битовые поля

#include "tset.h"

// Fake variables used as placeholders in tests
static const int FAKE_INT = -1;
static TBitField FAKE_BITFIELD(1);
static TSet FAKE_SET(1);

TSet::TSet(int mp) : BitField(mp/sizeof(TELEM))
{
    this->MaxPower = mp;
   
}

// конструктор копирования
TSet::TSet(const TSet &s) : BitField(this->MaxPower / sizeof(TELEM))
{
    this->MaxPower = s.MaxPower;
    this->BitField = s.BitField;

}

// конструктор преобразования типа
TSet::TSet(const TBitField &bf) : BitField(bf.GetLength()/ sizeof(TELEM))
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
    int res = 0;
    if (Elem > -1) {
        int count=0;
        while (count <= Elem) {
            if (this->BitField.GetBit(res) == 1) {
                count++;
            }
            res++;
        }
        return res;
    }
    else {
        cout << "ERROR" << endl;
        return -1;
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

TSet& TSet::operator=(const TSet &s) // присваивание
{
    this->BitField = s.BitField;
    return (*this);
}

int TSet::operator==(const TSet &s) const // сравнение
{
    if (this->MaxPower == s.MaxPower) {
       if(this->BitField == s.BitField){
           return 1;
        }
       else {
           return 0;
       }
    }
    else {
        cout << "dfrnt MP" << endl;
        return 0;
    }
}

int TSet::operator!=(const TSet &s) const // сравнение
{
    return (!(this == &s));
}

TSet TSet::operator+(const TSet &s) // объединение
{
    TSet res(this->MaxPower);
    if (this->MaxPower == s.MaxPower) {
        res.BitField = this->BitField | s.BitField;
        return res;
    }
    else {
        cout << "dfrnt MP" << endl;
        return *this;
    }
}

TSet TSet::operator+(const int Elem) // объединение с элементом
{
    this->InsElem(Elem);
    return (*this);
}

TSet TSet::operator-(const int Elem) // разность с элементом
{
    this->DelElem(Elem);
    return *this;
}

TSet TSet::operator*(const TSet &s) // пересечение
{
    TSet res(this->MaxPower);
        if (this->MaxPower == s.MaxPower) {
            res.BitField = this->BitField & s.BitField;
            return res;
        }
        else {
            cout << "dfrnt MP" << endl;
            return *this;
        }
   
}

TSet TSet::operator~(void) // дополнение
{
    TSet res(this->MaxPower);
    res.BitField = ~(this->BitField);
    return res;
}

// перегрузка ввода/вывода

istream &operator>>(istream &istr, TSet &s) // ввод
{
    return istr;
}

ostream& operator<<(ostream &ostr, const TSet &s) // вывод
{
    return ostr;
}
