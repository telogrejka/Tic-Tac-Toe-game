#include "xml.h"

XML::XML() {}

QDomElement XML::record(QDomDocument &domDoc, const QString &playerName, const QString &points, const QString &date)
{
    QDomElement domElement = makeElement(domDoc, "record", points, date);
    domElement.appendChild(makeElement(domDoc, "playerName", "", playerName));
    domElement.appendChild(makeElement(domDoc, "points", "", points));
    domElement.appendChild(makeElement(domDoc, "date", "", date));

    return domElement;
}

QDomElement XML::makeElement(QDomDocument &domDoc, const QString &playerName, const QString &points, const QString &date)
{
    QDomElement domElement = domDoc.createElement(playerName);

    if (!points.isEmpty())
    {
        QDomAttr domAttr = domDoc.createAttribute(points);
        domAttr.setValue(points);
        domElement.setAttributeNode(domAttr);
    }

    if (!date.isEmpty())
    {
        QDomText domText = domDoc.createTextNode(date);
        domElement.appendChild(domText);
    }
    return domElement;
}

void XML::traverseNode(const QDomNode &node)
{
    QDomNode domNode = node.firstChild();
       while(!domNode.isNull()) {
           if(domNode.isElement()) {
              QDomElement domElement = domNode.toElement();
              if(!domElement.isNull()) {
                  if(domElement.tagName() == "record")
                  {
                      qDebug() << "Attr: "
                               << domElement.attribute("points", "");
                  }
                  else
                  {
                      qDebug() << "TagName: " << domElement.tagName()
                               << "\tText: " << domElement.text();
                 }
              }
           }
           traverseNode(domNode);
           domNode = domNode.nextSibling();
        }
}
