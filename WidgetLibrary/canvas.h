#ifndef CANVAS_H
#define CANVAS_H

#include <QObject>
#include <QSizeF>
#include <QVector3D>
#include <QVector2D>
#include <QMatrix4x4>

#include <utility>

/* Rectangle window */
class Canvas : public QObject
{
    Q_OBJECT
public:
    Canvas(QObject *parent=nullptr);

    // generate projection matrix
    QMatrix4x4 getProjectionMatrix();

    // move canvas for given offset
    void moveCanvas(QVector2D delta);
    // center canvas on given point
    void centerIn(QVector2D point);
    // set new canvas size
    void setCanvasSize(QSizeF newSize);
    // set scaling factor
    void setScale(qreal factor);

    // get center position
    QPoint getCenter() const;

    // map screen coordinates to canvas coordinates
    QVector2D screenToCanvas(QVector2D point);

signals:
    // emits when matrix is updated
    void canvasChanged();

private:
    // get left lower and right upper angle
    std::pair<QVector2D, QVector2D> getBox();

    QSizeF m_canvasSize;
    QVector3D m_center;
    qreal m_scale;
};

#endif // CANVAS_H
