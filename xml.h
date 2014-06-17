#ifndef XML_H
#define XML_H

#include <QtXml>
#include <QXmlStreamReader>

class XML
{
public:
    XML();
    QDomElement record(      QDomDocument& domDoc,
                        const QString&      playerName,
                        const QString&      points,
                        const QString&      date
                       );

    void traverseNode(const QDomNode& node);

private:
    QDomElement makeElement(      QDomDocument& domDoc,
                            const QString&      playerName,
                            const QString&      points,
                            const QString&      date
                           );
};

#endif // XML_H
