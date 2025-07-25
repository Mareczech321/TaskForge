#pragma once

#ifndef COMMANDS_H
#define COMMANDS_H
#include <string>

enum Controls;
Controls getCommand(std::string const& input);
void Commands();

#endif