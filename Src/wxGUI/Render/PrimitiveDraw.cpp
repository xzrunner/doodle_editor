#include "PrimitiveDraw.h"
#include "GL10.h"

using namespace wxgui;

void PrimitiveDraw::resetColorAndTexture()
{
	GL10::BindTexture(GL10::GL_TEXTURE_2D, NULL);
	GL10::Color4f(1, 1, 1, 1);
}

void PrimitiveDraw::drawSquare(const f2Vec2& center, float radius, const f2Colorf& color)
{
	GL10::Color4f(color.r, color.g, color.b, color.a);
	GL10::Begin(GL10::GL_QUADS);
		GL10::Vertex2f(center.x - radius, center.y - radius);
		GL10::Vertex2f(center.x + radius, center.y - radius);
		GL10::Vertex2f(center.x + radius, center.y + radius);
		GL10::Vertex2f(center.x - radius, center.y + radius);
	GL10::End();
}

void PrimitiveDraw::drawSquareFrame(const f2Vec2& center, float radius, const f2Colorf& color)
{
	GL10::Color4f(color.r, color.g, color.b, color.a);
	GL10::Begin(GL10::GL_LINE_LOOP);
		GL10::Vertex2f(center.x - radius, center.y - radius);
		GL10::Vertex2f(center.x + radius, center.y - radius);
		GL10::Vertex2f(center.x + radius, center.y + radius);
		GL10::Vertex2f(center.x - radius, center.y + radius);
	GL10::End();
}

void PrimitiveDraw::drawRectangle(const f2Vec2& center, float width, float height, const f2Colorf& color)
{
	float hWidth = width * 0.5f;
	float hHeight = height * 0.5f;

	GL10::Color4f(color.r, color.g, color.b, color.a);
	GL10::Begin(GL10::GL_QUADS);
		GL10::Vertex2f(center.x - hWidth, center.y - hHeight);
		GL10::Vertex2f(center.x + hWidth, center.y - hHeight);
		GL10::Vertex2f(center.x + hWidth, center.y + hHeight);
		GL10::Vertex2f(center.x - hWidth, center.y + hHeight);
	GL10::End();
}

void PrimitiveDraw::drawRing(const f2Vec2& center, float radius, const f2Colorf& color, int size /*= 3*/, int kSegments /*= 16*/)
{
	GL10::LineWidth(size);

	GL10::Color3f(color.r, color.g, color.b);
	const float k_increment = 2.0f * PI / kSegments;
	float theta = 0.0f;
	GL10::Begin(GL10::GL_LINE_LOOP);
	for (size_t i = 0; i < kSegments; ++i)
	{
		f2Vec2 v = center + f2Vec2(cosf(theta), sinf(theta)) * radius;
		GL10::Vertex2f(v.x, v.y);
		theta += k_increment;
	}
	GL10::End();

	GL10::LineWidth(1.0f);
}

void PrimitiveDraw::drawCircle(const f2Vec2& center, float radius, const f2Colorf& color)
{
	const int k_segments = 16;
	const float k_increment = 2.0f * PI / k_segments;
	float theta = 0.0f;

	std::vector<f2Vec2> vertices;
	std::vector<f2Colorf> colors;
	vertices.reserve(k_segments + 2);
	colors.reserve(k_segments + 2);
	vertices.push_back(center);
	colors.push_back(color);
	for (size_t i = 0; i < k_segments; ++i)
	{
		f2Vec2 v = center + f2Vec2(cosf(theta), sinf(theta)) * radius;
		vertices.push_back(v);
		colors.push_back(color);
		theta += k_increment;
	}
	vertices.push_back(vertices[1]);
	colors.push_back(color);

	GL10::Enable(GL10::GL_BLEND);
	GL10::BlendFunc(GL10::GL_SRC_ALPHA, GL10::GL_ONE_MINUS_SRC_ALPHA);

 	GL10::EnableClientState(GL10::GL_VERTEX_ARRAY);
 	GL10::EnableClientState(GL10::GL_COLOR_ARRAY);

	GL10::VertexPointer(2, GL10::GL_FLOAT, 0, &vertices[0]);
	GL10::ColorPointer(4, GL10::GL_FLOAT, 0, &colors[0]);

	GL10::DrawArrays(GL10::GL_TRIANGLE_FAN, 0, vertices.size());

 	GL10::DisableClientState(GL10::GL_COLOR_ARRAY);
 	GL10::DisableClientState(GL10::GL_VERTEX_ARRAY);

	GL10::Disable(GL10::GL_BLEND);
}

void PrimitiveDraw::drawCircles(const std::vector<f2Vec2>& circles, float radius, const f2Colorf& color)
{
	if (circles.empty()) return;

	const int k_segments = 8;
	const float k_increment = 2.0f * PI / k_segments;

	std::vector<f2Vec2> vertices;
	std::vector<f2Colorf> colors;
	const int size = k_segments * circles.size() * 3;

	vertices.reserve(size);
	colors.resize(size, color);
	for (size_t i = 0, n = circles.size(); i < n; ++i)
	{
		float theta = 0.0f;
		f2Vec2 lastPos;
		for (size_t j = 0; j < k_segments; ++j)
		{
			if (j == 0)
				vertices.push_back(circles[i] + f2Vec2(cosf(theta), sinf(theta)) * radius);
			else
				vertices.push_back(lastPos);
			lastPos = circles[i] + f2Vec2(cosf(theta + k_increment), sinf(theta + k_increment)) * radius;
			vertices.push_back(lastPos);
			vertices.push_back(circles[i]);

			theta += k_increment;
		}
	}

	GL10::Enable(GL10::GL_BLEND);
	GL10::BlendFunc(GL10::GL_SRC_ALPHA, GL10::GL_ONE_MINUS_SRC_ALPHA);

 	GL10::EnableClientState(GL10::GL_VERTEX_ARRAY);
 	GL10::EnableClientState(GL10::GL_COLOR_ARRAY);

	GL10::VertexPointer(2, GL10::GL_FLOAT, 0, &vertices[0]);
	GL10::ColorPointer(4, GL10::GL_FLOAT, 0, &colors[0]);

	GL10::DrawArrays(GL10::GL_TRIANGLES, 0, vertices.size());

 	GL10::DisableClientState(GL10::GL_COLOR_ARRAY);
 	GL10::DisableClientState(GL10::GL_VERTEX_ARRAY);

	GL10::Disable(GL10::GL_BLEND);
}

void PrimitiveDraw::drawPoints(const std::vector<f2Vec2>& vertices, const f2Colorf& color, int size/* = 3*/)
{
	GL10::PointSize(size);

	GL10::EnableClientState(GL10::GL_VERTEX_ARRAY);
	GL10::EnableClientState(GL10::GL_COLOR_ARRAY);

	std::vector<f2Colorf> colors(vertices.size(), color);

	GL10::VertexPointer(2, GL10::GL_FLOAT, 0, &vertices[0]);
	GL10::ColorPointer(4, GL10::GL_FLOAT, 0, &colors[0]);

	GL10::DrawArrays(GL10::GL_POINTS, 0, vertices.size());

	GL10::DisableClientState(GL10::GL_COLOR_ARRAY);
	GL10::DisableClientState(GL10::GL_VERTEX_ARRAY);

	GL10::PointSize(1.0f);
}

void PrimitiveDraw::drawLine(const f2Vec2& p0, const f2Vec2& p1, 
							 const f2Colorf& color, int size/* = 3*/)
{
	GL10::LineWidth(size);

	GL10::Color4f(color.r, color.g, color.b, color.a);

	GL10::Begin(GL10::GL_LINES);
		GL10::Vertex2f(p0.x, p0.y); 
		GL10::Vertex2f(p1.x, p1.y);
	GL10::End();

	GL10::LineWidth(1.0f);
}

void PrimitiveDraw::drawDotLine(const f2Vec2& p0, const f2Vec2& p1, 
								const f2Colorf& color, int size /*= 3*/)
{
	wxgui::GL10::Enable(wxgui::GL10::GL_LINE_STIPPLE);

	wxgui::GL10::LineStipple(1, 0x0101);
	wxgui::PrimitiveDraw::drawLine(p0, p1, color, size);

	wxgui::GL10::Disable(wxgui::GL10::GL_LINE_STIPPLE);
}

void PrimitiveDraw::drawDashLine(const f2Vec2& p0, const f2Vec2& p1, 
								 const f2Colorf& color, int size /*= 3*/)
{
	wxgui::GL10::Enable(wxgui::GL10::GL_LINE_STIPPLE);

	wxgui::GL10::LineStipple(1, 0x00FF);
	wxgui::PrimitiveDraw::drawLine(p0, p1, color, size);

	wxgui::GL10::Disable(wxgui::GL10::GL_LINE_STIPPLE);
}

void PrimitiveDraw::drawDotDashLine(const f2Vec2& p0, const f2Vec2& p1, 
									const f2Colorf& color, int size /*= 3*/)
{
	wxgui::GL10::Enable(wxgui::GL10::GL_LINE_STIPPLE);

	wxgui::GL10::LineStipple(1, 0x1c47);
	wxgui::PrimitiveDraw::drawLine(p0, p1, color, size);

	wxgui::GL10::Disable(wxgui::GL10::GL_LINE_STIPPLE);
}

void PrimitiveDraw::drawLines(const std::vector<f2Vec2>& vertices, 
							  const f2Colorf& color, int size /*= 3*/)
{
	GL10::LineWidth(size);

	GL10::EnableClientState(GL10::GL_VERTEX_ARRAY);
	GL10::EnableClientState(GL10::GL_COLOR_ARRAY);

	std::vector<f2Colorf> colors(vertices.size(), color);

	GL10::VertexPointer(2, GL10::GL_FLOAT, 0, &vertices[0]);
	GL10::ColorPointer(4, GL10::GL_FLOAT, 0, &colors[0]);

	GL10::DrawArrays(GL10::GL_LINES, 0, vertices.size());

	GL10::DisableClientState(GL10::GL_COLOR_ARRAY);
	GL10::DisableClientState(GL10::GL_VERTEX_ARRAY);

	GL10::LineWidth(1.0f);
}

void PrimitiveDraw::drawPolyline(const std::vector<f2Vec2>& vertices, 
								 const f2Colorf& color, bool isClose, int size /*= 3*/)
{
	GL10::LineWidth(size);

 	GL10::EnableClientState(GL10::GL_VERTEX_ARRAY);
  	GL10::EnableClientState(GL10::GL_COLOR_ARRAY);
 
 	std::vector<f2Colorf> colors(vertices.size(), color);

	GL10::VertexPointer(2, GL10::GL_FLOAT, 0, &vertices[0]);
	GL10::ColorPointer(4, GL10::GL_FLOAT, 0, &colors[0]);

	if (isClose)
		GL10::DrawArrays(GL10::GL_LINE_LOOP, 0, vertices.size());
	else
		GL10::DrawArrays(GL10::GL_LINE_STRIP, 0, vertices.size());

 	GL10::DisableClientState(GL10::GL_COLOR_ARRAY);
 	GL10::DisableClientState(GL10::GL_VERTEX_ARRAY);

	GL10::LineWidth(1.0f);
}

void PrimitiveDraw::drawPolygon(const std::vector<f2Vec2>& vertices, const f2Colorf& color)
{
	GL10::Enable(GL10::GL_BLEND);
	GL10::BlendFunc(GL10::GL_SRC_ALPHA, GL10::GL_ONE_MINUS_SRC_ALPHA);

	GL10::EnableClientState(GL10::GL_VERTEX_ARRAY);
	GL10::EnableClientState(GL10::GL_COLOR_ARRAY);

	std::vector<f2Colorf> colors(vertices.size(), color);

	GL10::VertexPointer(2, GL10::GL_FLOAT, 0, &vertices[0]);
	GL10::ColorPointer(4, GL10::GL_FLOAT, 0, &colors[0]);

	GL10::DrawArrays(GL10::GL_POLYGON, 0, vertices.size());

	GL10::DisableClientState(GL10::GL_COLOR_ARRAY);
	GL10::DisableClientState(GL10::GL_VERTEX_ARRAY);

	GL10::Disable(GL10::GL_BLEND);
}

void PrimitiveDraw::drawTriangles(const std::vector<f2Vec2>& triangles, const f2Colorf& color)
{
	if (triangles.empty()) return;

	std::vector<f2Colorf> colors;
	colors.resize(triangles.size(), color);

 	GL10::EnableClientState(GL10::GL_VERTEX_ARRAY);
 	GL10::EnableClientState(GL10::GL_COLOR_ARRAY);

	GL10::VertexPointer(2, GL10::GL_FLOAT, 0, &triangles[0]);
	GL10::ColorPointer(4, GL10::GL_FLOAT, 0, &colors[0]);

	GL10::DrawArrays(GL10::GL_TRIANGLES, 0, triangles.size());

 	GL10::DisableClientState(GL10::GL_COLOR_ARRAY);
 	GL10::DisableClientState(GL10::GL_VERTEX_ARRAY);
}

//void PrimitiveDraw::drawTriangles(const std::vector<f2Vec2>& triangles, const wxString& filepath)
//{
//	if (triangles.empty()) return;
//
//	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
//
//	glClearStencil(0);
//	glEnable(GL_STENCIL_TEST);
//
//	glClear(GL_STENCIL_BUFFER_BIT); 
//
// 	glStencilFunc(GL_NEVER, 0x0, 0x0);
// 	glStencilOp(GL_INCR, GL_INCR, GL_INCR);
//	{
//		glEnableClientState(GL_VERTEX_ARRAY);
//		glVertexPointer(2, GL_FLOAT, 0, &triangles[0]);
//		glDrawArrays(GL_TRIANGLES, 0, (GLsizei)triangles.size());
//		glDisableClientState(GL_VERTEX_ARRAY);
//	}
// 	glStencilFunc(GL_NOTEQUAL, 0x0, 0x1);
// 	glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);
//	{
//		Symbol* symbol = SymbolMgr::Instance()->getItem(filepath);
//
//		unsigned int id;
//		float width, height;
//		symbol->getTextureInfo(id, width, height);
//
//		f2Vec2 leftLow(FLOAT_MAX, FLOAT_MAX), rightTop(-FLOAT_MAX, -FLOAT_MAX);
//		for (size_t i = 0, n = triangles.size(); i < n; ++i)
//		{
//			const f2Vec2& pos = triangles[i];
//			if (pos.x < leftLow.x) leftLow.x = pos.x;
//			if (pos.x > rightTop.x) rightTop.x = pos.x;
//			if (pos.y < leftLow.y) leftLow.y = pos.y;
//			if (pos.y > rightTop.y) rightTop.y = pos.y;
//		}
//
//		const size_t count = std::ceil((rightTop.x - leftLow.x) / width)
//			* std::ceil((rightTop.y - leftLow.y) / height);
//
//		std::vector<f2Vec2> vertices;
//		std::vector<GLushort> indices;
//		vertices.reserve(count * 4 * 2);
//		indices.reserve(count * 6);
//		int index = 0;
//		for (float x = leftLow.x; x < rightTop.x; x += width)
//		{
//			for (float y = leftLow.y; y < rightTop.y; y += height)
//			{
//				vertices.push_back(f2Vec2(x, y));
//				vertices.push_back(f2Vec2(0, 0));
//
//				vertices.push_back(f2Vec2(x + width, y));
//				vertices.push_back(f2Vec2(1, 0));
//
//				vertices.push_back(f2Vec2(x + width, y + height));
//				vertices.push_back(f2Vec2(1, 1));
//
//				vertices.push_back(f2Vec2(x, y + height));
//				vertices.push_back(f2Vec2(0, 1));
//
//				indices.push_back(index + 0);
//				indices.push_back(index + 1);
//				indices.push_back(index + 2);
//
//				indices.push_back(index + 0);
//				indices.push_back(index + 2);
//				indices.push_back(index + 3);
//
//				index += 4;
//			}
//		}
//
//		glBindTexture(GL_TEXTURE_2D, id);
//
//		glEnableClientState(GL_VERTEX_ARRAY);
//		glVertexPointer(2, GL_FLOAT, sizeof(float) * 4, &vertices[0]);
//
//		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
//		glTexCoordPointer(2, GL_FLOAT, sizeof(float) * 4, &vertices[1]);
//
//		glDrawElements(GL_TRIANGLES, vertices.size() * 3 / 4, GL_UNSIGNED_SHORT, &indices[0]);
//
//		glDisableClientState(GL_VERTEX_ARRAY);
//		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
//
//		glBindTexture(GL_TEXTURE_2D, NULL);
//	}
//	glDisable(GL_STENCIL_TEST);
//}
//
//void PrimitiveDraw::drawTriangles(const std::vector<f2Vec2>& triangles, const wxString& filepath, 
//						   const f2Vec2& leftLow, const const std::vector<unsigned int>& mesh)
//{
//	if (triangles.empty()) return;
//
//	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
//
//	glClearStencil(0);
//	glEnable(GL_STENCIL_TEST);
//
//	glClear(GL_STENCIL_BUFFER_BIT); 
//
// 	glStencilFunc(GL_NEVER, 0x0, 0x0);
// 	glStencilOp(GL_INCR, GL_INCR, GL_INCR);
//	{
//		glEnableClientState(GL_VERTEX_ARRAY);
//		glVertexPointer(2, GL_FLOAT, 0, &triangles[0]);
//		glDrawArrays(GL_TRIANGLES, 0, (GLsizei)triangles.size());
//		glDisableClientState(GL_VERTEX_ARRAY);
//	}
// 	glStencilFunc(GL_NOTEQUAL, 0x0, 0x1);
// 	glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);
//	{
//		Symbol* symbol = SymbolMgr::Instance()->getItem(filepath);
//
//		unsigned int id;
//		float width, height;
//		symbol->getTextureInfo(id, width, height);
//
//		std::vector<f2Vec2> vertices;
//		std::vector<GLushort> indices;
//		vertices.reserve(mesh.size() * 4 * 2);
//		indices.reserve(mesh.size() * 6);
//		int index = 0;
//		for (size_t i = 0, n = mesh.size(); i < n; ++i)
//		{
//			int pos = mesh[i];
//			float left = leftLow.x + (pos & 0x0000ffff) * width;
//			float low = leftLow.y + (pos >> 16) * height;
//
//			vertices.push_back(f2Vec2(left, low));
//			vertices.push_back(f2Vec2(0, 0));
//
//			vertices.push_back(f2Vec2(left + width, low));
//			vertices.push_back(f2Vec2(1, 0));
//
//			vertices.push_back(f2Vec2(left + width, low + height));
//			vertices.push_back(f2Vec2(1, 1));
//
//			vertices.push_back(f2Vec2(left, low + height));
//			vertices.push_back(f2Vec2(0, 1));
//
//			indices.push_back(index + 0);
//			indices.push_back(index + 1);
//			indices.push_back(index + 2);
//
//			indices.push_back(index + 0);
//			indices.push_back(index + 2);
//			indices.push_back(index + 3);
//
//			index += 4;
//		}
//
//		glBindTexture(GL_TEXTURE_2D, id);
//
//		glEnableClientState(GL_VERTEX_ARRAY);
//		glVertexPointer(2, GL_FLOAT, sizeof(float) * 4, &vertices[0]);
//
//		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
//		glTexCoordPointer(2, GL_FLOAT, sizeof(float) * 4, &vertices[1]);
//
//		glDrawElements(GL_TRIANGLES, vertices.size() * 3 / 4, GL_UNSIGNED_SHORT, &indices[0]);
//
//		glDisableClientState(GL_VERTEX_ARRAY);
//		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
//
//		glBindTexture(GL_TEXTURE_2D, NULL);
//	}
//	glDisable(GL_STENCIL_TEST);
//}

void PrimitiveDraw::drawTriangles(unsigned int texID, const std::vector<f2Vec2>& triangles, 
								  const std::vector<f2Vec2>& texCoords)
{
	if (triangles.empty()) return;

	GL10::BindTexture(GL10::GL_TEXTURE_2D, texID);

	GL10::EnableClientState(GL10::GL_VERTEX_ARRAY);
	GL10::EnableClientState(GL10::GL_TEXTURE_COORD_ARRAY);

	GL10::VertexPointer(2, GL10::GL_FLOAT, 0, &triangles[0]);
	GL10::TexCoordPointer(2, GL10::GL_FLOAT, 0, &texCoords[0]);

	GL10::DrawArrays(GL10::GL_TRIANGLES, 0, triangles.size());

	GL10::DisableClientState(GL10::GL_TEXTURE_COORD_ARRAY);
	GL10::DisableClientState(GL10::GL_VERTEX_ARRAY);

	GL10::BindTexture(GL10::GL_TEXTURE_2D, NULL);
}
 //
 //void PrimitiveDraw::drawMesh(unsigned int texID, const std::vector<f2Vec2>& vertices, 
 //							 const std::vector<f2Vec2>& texCoords)
 //{
 //	GL10::Enable(GL10::GL_BLEND);
 //	GL10::BlendFunc(GL10::GL_SRC_ALPHA, GL10::GL_ONE_MINUS_SRC_ALPHA);
 //
 //	GL10::Color4f(1.0f, 1.0f, 1.0f, 1.0f);
 //
 //	GL10::PushMatrix();
 //
 //	//	glActiveTexture(GL_TEXTURE0);
 //	GL10::BindTexture(GL10::GL_TEXTURE_2D, texID);
 //
 //	GL10::EnableClientState(GL10::GL_VERTEX_ARRAY);
 //	GL10::VertexPointer(2, GL10::GL_FLOAT, sizeof(f2Vec2), &vertices[0]);
 //
 //	GL10::EnableClientState(GL10::GL_TEXTURE_COORD_ARRAY);
 //	GL10::TexCoordPointer(2, GL10::GL_FLOAT, sizeof(f2Vec2), &texCoords[0]);
 //
 //	GL10::DrawArrays(GL10::GL_TRIANGLES, 0, vertices.size());
 //
 //	GL10::DisableClientState(GL10::GL_VERTEX_ARRAY);
	//GL10::DisableClientState(GL10::GL_TEXTURE_COORD_ARRAY);
	//GL10::DisableClientState(GL10::GL_COLOR_ARRAY);
 //
 //	GL10::BindTexture(GL10::GL_TEXTURE_2D, NULL);
 //
 //	GL10::PopMatrix();
 //
 //	GL10::Disable(GL10::GL_BLEND);
 //}

void PrimitiveDraw::drawTrianglesSlow(unsigned int texID, const std::vector<f2Vec2>& triangles, 
									  const std::vector<f2Vec2>& texCoords)
{
	if (triangles.empty()) return;

	GL10::Enable(GL10::GL_BLEND);
	GL10::BlendFunc(GL10::GL_SRC_ALPHA, GL10::GL_ONE_MINUS_SRC_ALPHA);

	GL10::Color4f(1.0f, 1.0f, 1.0f, 1.0f);

	GL10::BindTexture(GL10::GL_TEXTURE_2D, texID);
	GL10::Begin(GL10::GL_TRIANGLES);
	for (size_t i = 0, n = triangles.size(); i < n; ++i)
	{
		GL10::TexCoord2f(texCoords[i].x, texCoords[i].y);
		GL10::Vertex3f(triangles[i].x, triangles[i].y, -1.0f);
	}
	GL10::End();
	GL10::BindTexture(GL10::GL_TEXTURE_2D, NULL);

	GL10::Disable(GL10::GL_BLEND);
}