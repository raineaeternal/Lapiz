#pragma once

#ifndef REGISTER
#define REGISTER(void, method) Lapiz::Register<void>(method, const char*);
#endif
