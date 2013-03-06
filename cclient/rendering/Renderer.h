#ifndef _RENDERER_H
#define _RENDERER_H

#include "../vector.h"
#include "../matrix.h"

class Sprite;
class Animation;
class Scene;

class SDL_Surface;

enum RendererDrawMode {
	DRAW_MODE_VIEWPORT,
	DRAW_MODE_SCENE
};

class Renderer {
public:
	Renderer();

	const Vector2 &getViewportPos() const;
	void setViewportPos(const Vector2 &pos);

	const Matrix3x3 &getTransform() const;
	void setTransform(const Matrix3x3 &transform);

	Matrix3x3 getDefaultTransform() const;

	RendererDrawMode getDrawMode() const;
	void setDrawMode(RendererDrawMode drawMode);

	void drawScene(Scene *scene);

	virtual void swapBuffer() = 0;

	virtual void init(int screenWidth, int screenHeight) = 0;
	virtual void uninit() = 0;

	virtual void drawAnimationFrame(const Vector2 &pos, const Vector2 &size, int frame, Animation *anim) = 0;

	virtual void fillRect(const Vector4 &bounds, const Vector4 &color) = 0;

private:
	Vector2 viewportPos;

	Matrix3x3 transform;
};



#endif
