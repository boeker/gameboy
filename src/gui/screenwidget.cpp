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

    // TODO - save size for use in paintGL()
}

void ScreenWidget::paintGL() {
    glClear(GL_COLOR_BUFFER_BIT);

    glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, 160, 144, GL_RGB, GL_UNSIGNED_BYTE, reinterpret_cast<GLvoid*>(framebuffer));

    glBegin(GL_QUADS);
        glTexCoord2d(0.0, 0.0);
        glVertex2d(0.0, 0.0);
        glTexCoord2d(1.0, 0.0);
        glVertex2d(160.0, 0.0); // TODO - display_width!
        glTexCoord2d(1.0, 1.0);
        glVertex2d(160.0, 144.0); // TODO - display_width, display_height!
        glTexCoord2d(0.0, 1.0);
        glVertex2d(0.0, 144.0); // TODO - display_height!
    glEnd();
}
