#pragma once

#include <QAtomicPointer>
#include <QMutex>

namespace FW
{
    template <class T>
    class GlobalStaticDeleter
    {
    public:
        GlobalStaticDeleter(T *t) : m_instance(t) {}
        ~GlobalStaticDeleter() { delete m_instance; }
    private:
        T *m_instance;
    };

    template <class T>
    class FWSingleton
    {
    public:
        static T* instance()
        {
            if (!_instance)
            {
                QMutexLocker guard{&_mutex};
                if (!_instance)
                {
                    _instance = new T;
                    static GlobalStaticDeleter<T> cleanup(_instance.load());
                    Q_UNUSED(cleanup)
                }
            }
            return _instance;
        }

        static bool isInstantiated()
        {
            return _instance ? true : false;
        }

    private:

        FWSingleton() {}
        ~FWSingleton() {}

        static QMutex _mutex;
        static QAtomicPointer<T> _instance;
    };

    template<class T> QMutex FWSingleton<T>::_mutex;
    template<class T> QAtomicPointer<T> FWSingleton<T>::_instance;
}
