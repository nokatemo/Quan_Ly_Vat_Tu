#ifndef VALIDATE_H
#define VALIDATE_H

#include <string>
#include <cstddef>

// Khai bao cac ham: chi co ten, tham so, kieu tra ve va dau ;.
void chuanhoaten(std::string& str);

bool namnhuan(int nam);

int kiemtrangay(int thang, int nam);

bool ngayhople(int ngay, int thang, int nam);

int nhapluachon();

bool conso(const std::string& ten);

std::string NhapMaID(std::size_t maxlen);

int nhapsonguyen();

#endif


