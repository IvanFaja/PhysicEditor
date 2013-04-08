#ifndef FREEDRAWER_H
#define FREEDRAWER_H

#include <QQuickItem>
#include <QVector>
struct Point{
    Point(float x, float y):x(x),y(y){

    }
    Point():x(0),y(0){

    }
    float x;
    float y;
};
class FreeDrawer : public QQuickItem
{
    Q_OBJECT
    Q_PROPERTY(QString path READ path WRITE setPath)
    Q_PROPERTY(QString fileName READ fileName WRITE setFileName)
public:
    FreeDrawer( QQuickItem *parent = 0);
    ~FreeDrawer();
    QSGNode * updatePaintNode(QSGNode *oldNode, UpdatePaintNodeData *);
    Q_INVOKABLE void addVertice(float x, float y);

    Q_INVOKABLE void clear(){
        update();
        m_vertices.clear();}

    Q_INVOKABLE void save();

    QString path(){return m_path;}
    void setPath(QString path);

    QString fileName(){return m_fileName;}
    void setFileName(QString name){m_fileName = name;}

signals:
    void drawChange(bool);
    void saveEnd();
private:
    QVector<Point> m_vertices;
    QString m_path;
    QString m_fileName;
};

#endif // FREEDRAWER_H
