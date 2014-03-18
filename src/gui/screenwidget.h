#ifndef GUI_SCREENWIDGET_H
#define GUI_SCREENWIDGET_H

#include <QGLWidget>
#include <atomic>
#include "util/color.h"

class ScreenWidget : public QGLWidget {
 public:
    explicit ScreenWidget(QWidget *parent);
    void setFramebuffer(util::Color *fb);
    void resizeEvent(QResizeEvent *event);
    void paintEvent(QPaintEvent *);
    void resizePub(int w, int h);

    std::atomic<bool> resizeNeeded;
    std::atomic<int> newWidth;
    std::atomic<int> newHeight;

 protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();
 private:
    util::Color* framebuffer;

    int width;
    int height;
};

#endif
