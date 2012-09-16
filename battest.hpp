#ifndef _ENERGY_TEST_HPP_
#define _ENERGY_TEST_HPP_

#include <QObject>

#include <contextproperty.h>
#include <functional>


typedef void (*prop_fn_t)(QString const &, QVariant const &);

class Test : public QObject
{
        Q_OBJECT;
public:
        Test(QString name, prop_fn_t fn)
                : QObject(0)
                , name(name)
                , prop(name)
                , fn(fn)
        {
                connect(&prop, SIGNAL(valueChanged()),
                        this, SLOT(onValueChanged()));
                prop.subscribe();
        }

        ~Test()
        {
                prop.unsubscribe();
                disconnect(&prop, SIGNAL(valueChanged()),
                           this, SLOT(onValueChanged()));
        }

private slots:
        void onValueChanged()
        {
                fn(name, prop.value());
        }

private:
        ContextProperty prop;
        QString name;
        prop_fn_t fn;
};

#endif // _ENERGY_TEST_HPP_
