#include "stdafx.h"
#include "Renderer.h"


Renderer::Renderer()
{
}


Renderer::~Renderer()
{
}

void Renderer::prepare()
{
	glClearColor(1,0,0,1);
	glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer::render(RawModel model)
{
	glEnableClientState(GL_VERTEX_ARRAY);
	glDrawArrays(GL_TRIANGLES, 0, model.getVertexCount());
	glDisableClientState(GL_VERTEX_ARRAY);
}
