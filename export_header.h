// Copyright 2020 Oleksandr Matasov
// export_header.h msvc import/export draft for server library [TBD]
#ifdef _WIN32
#ifndef _SERVER_EXPORTS_H__
#define _SERVER_EXPORTS_H__

#ifdef _WIN32
#ifdef SERVER_EXPORTS
#define SERVER_EXPORT __declspec(dllexport)
#else
#define SERVER_EXPORT __declspec(dllimport)
#endif
#else
#define SERVER_EXPORT
#endif
#endif
#endif /* _SERVER_EXPORTS_H__ */
