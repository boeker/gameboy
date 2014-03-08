#include "screenwidget.h"


ScreenWidget::ScreenWidget(QWidget *parent) :
    QGLWidget(parent) {
}

void ScreenWidget::setFramebuffer(util::Color *fb) {
    framebuffer = fb;
}

void ScreenWidget::resizeEvent(QResizeEvent *event) {
	//do nothing
}

void ScreenWidget::paintEvent(QPaintEvent *event) {
	//do nothing
}

void ScreenWidget::initializeGL() {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, 160, 0, 144, 0, 1);
    glMatrixMode(GL_MODELVIEW);

    glShadeModel(GL_FLAT);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
}

void ScreenWidget::resizeGL(int w, int h) {
    glViewport(0, 0, w, h);
    //glPixelZoom((double)w/160.0, (double)h/144.0);
}

void ScreenWidget::paintGL() {
    glRasterPos2i(0,0);
    glDrawPixels(160, 144, GL_RGB, GL_UNSIGNED_BYTE, framebuffer);
}
