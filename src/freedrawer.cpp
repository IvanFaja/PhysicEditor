#include "freedrawer.h"
#include <QSGGeometryNode>
#include <QSGGeometry>
#include <QSGFlatColorMaterial>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QDir>

FreeDrawer::FreeDrawer( QQuickItem *parent ):QQuickItem(parent)
{
    setFlag(ItemHasContents, true);
}

FreeDrawer::~FreeDrawer()
{

}

QSGNode *FreeDrawer::updatePaintNode(QSGNode * oldNode, QQuickItem::UpdatePaintNodeData *)
{

    QSGGeometryNode *node = 0;
    QSGGeometry *geometry = 0;
    if(!oldNode){

        geometry = new QSGGeometry(QSGGeometry::defaultAttributes_Point2D(),
                                   m_vertices.size());
        geometry->setLineWidth(2);
        geometry->setDrawingMode(GL_LINE_STRIP);

        node = new QSGGeometryNode;
        node->setGeometry(geometry);
        node->setFlag(QSGNode::OwnsGeometry);

        QSGFlatColorMaterial *material = new QSGFlatColorMaterial;
        material->setColor(QColor(255, 0, 0));
        node->setMaterial(material);
        node->setFlag(QSGNode::OwnsMaterial);

    }else {
        node = static_cast<QSGGeometryNode *>(oldNode);
        geometry = node->geometry();
        geometry->allocate(m_vertices.size());
    }


      QSGGeometry::Point2D *vertices = geometry->vertexDataAsPoint2D();
      for(int i = 0; i< m_vertices.size();i++){
          vertices[i].set(m_vertices.at(i).x,
                          m_vertices.at(i).y);

      }

      return node;
}

void FreeDrawer::addVertice(float x, float y)
{
    m_vertices.append(Point(x,y));
    update();
}

void FreeDrawer::save()
{

    QJsonArray data;
    for(int i = 0; i< m_vertices.size();i++){
        Point dato = m_vertices.at(i);
        QJsonObject point;
        point.insert("x",dato.x);
        point.insert("y",dato.y);
        QJsonValue value(point);
        data.append(value);

    }
    Q_ASSERT(m_path.size() > 0);
    Q_ASSERT(m_fileName.size() > 0);

    QDir dir(m_path);
    QFile file(dir.filePath(m_fileName));
    dir.mkdir(m_path);
    qDebug()<<"file to save"<<file.fileName();
    if(file.open(QIODevice::WriteOnly)){
        QJsonDocument json;
        json.setArray(data);
        file.write(json.toJson());
        file.close();

        qDebug()<<"done";
    }else{
        qDebug()<<"failed";
    }

}

void FreeDrawer::setPath(QString path)
{
    QDir dir(path);
    QString name = dir.dirName();
    if(name.contains(".")){
     path.remove(path.lastIndexOf("/"),path.size()-path.lastIndexOf("/"));
     m_path = path;
     name.remove(name.lastIndexOf("."),name.size()-name.lastIndexOf("."));
     m_fileName = name.append(".json");
    }
}
