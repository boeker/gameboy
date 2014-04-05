#include "screenwidget.h"

#include <QResizeEvent>

ScreenWidget::ScreenWidget(const QGLFormat &format, QWidget *parent) :
    QGLWidget(format, parent),
    resizeNeeded(false),
    width(160),
    height(144) {
}

void ScreenWidget::setFramebuffer(util::Color *fb) {
    framebuffer = fb;
}

void ScreenWidget::resizeEvent(QResizeEvent *event) {
    newWidth = event->size().width();
    newHeight = event->size().height();
    resizeNeeded = true;
}

void ScreenWidget::paintEvent(QPaintEvent *) {
	//do nothing
}

void ScreenWidget::resizePub(int w, int h) {
    resizeGL(w, h);
}

void ScreenWidget::initializeGL() {
    glTexImage2D(GL_TEXTURE_2D, 0, 3, 160, 144, 0, GL_RGB, GL_UNSIGNED_BYTE, reinterpret_cast<GLvoid*>(framebuffer));

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

    glEnable(GL_TEXTURE_2D);
}

void ScreenWidget::resizeGL(int w, int h) {
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, w, h, 0, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glViewport(0, 0, w, h);

    width = w;
    height = h;
}

void ScreenWidget::paintGL() {
    glClear(GL_COLOR_BUFFER_BIT);

    glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, 160, 144, GL_RGB, GL_UNSIGNED_BYTE, reinterpret_cast<GLvoid*>(framebuffer));

    glBegin(GL_QUADS);
        glTexCoord2d(0.0, 0.0);
        glVertex2d(0.0, 0.0);
        glTexCoord2d(1.0, 0.0);
        glVertex2d(width, 0.0);
        glTexCoord2d(1.0, 1.0);
        glVertex2d(width, height);
        glTexCoord2d(0.0, 1.0);
        glVertex2d(0.0, height);
    glEnd();
}
