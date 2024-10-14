#ifndef RENDER_H
#define RENDER_H


void render();

#define SPRITE(x, y) ((Rectangle){ (x) * 16, (y) * 16, 16, 16})
#define UNIT(x) SPRITE(5 + (x), 5)

#endif // RENDER_H
