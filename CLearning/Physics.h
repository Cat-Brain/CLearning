#pragma once
#include "MarchingCubes.h"

bool SphereTriangleColliding(SphereCollider* s, Vertex vertices[3])
{
	// Create 7 booleans to store whether or not they pass the 7 steps.
	bool sep;

	// Create 3 vec3s that are the offsets from the position of the colider to each of the vertices of the triangles.
	vec3 a, b, c;
	glm_vec3_sub(vertices[0].pos, s->pos, a);
	glm_vec3_sub(vertices[1].pos, s->pos, b);
	glm_vec3_sub(vertices[2].pos, s->pos, c);
	vec3 al, bl, cl;
	glm_vec3_sub(vertices[0].pos, s->lastPos, al);
	glm_vec3_sub(vertices[1].pos, s->lastPos, bl);
	glm_vec3_sub(vertices[2].pos, s->lastPos, cl);

	float rr = s->radius * s->radius;


	float d = glm_vec3_dot(a, vertices[0].normal);
	float dl = glm_vec3_dot(al, vertices[0].normal);

	sep = fabsf(d) > s->radius && glm_signf(d) == glm_signf(dl);

	// Create six float to store the dot products of the 2 vec3s that are in their name.
	float aa, ab, ac, bb, bc, cc;

	aa = glm_vec3_dot(a, a);
	ab = glm_vec3_dot(a, b);
	ac = glm_vec3_dot(a, c);
	bb = glm_vec3_dot(b, b);
	bc = glm_vec3_dot(b, c);
	cc = glm_vec3_dot(c, c);

	float aal, abl, acl, bbl, bcl, ccl;

	aal = glm_vec3_dot(al, al);
	abl = glm_vec3_dot(al, bl);
	acl = glm_vec3_dot(al, cl);
	bbl = glm_vec3_dot(bl, bl);
	bcl = glm_vec3_dot(bl, cl);
	ccl = glm_vec3_dot(cl, cl);

	sep |= (aa > rr) && (ab > aa) && (ac > aa);// && (abl > aal) && (acl > aal);
	sep |= (bb > rr) && (ab > bb) && (bc > bb);// && (abl > bbl) && (bcl > bbl);
	sep |= (cc > rr) && (ac > cc) && (bc > cc);// && (acl > ccl) && (bcl > ccl);

	float d1, d2, d3;
	d1 = ab - aa;
	d2 = bc - bb;
	d3 = ac - cc;

	vec3 ba, ca, cb;
	glm_vec3_sub(b, a, ba);
	glm_vec3_sub(c, a, ca);
	glm_vec3_sub(c, b, cb);

	float e1, e2, e3;
	e1 = glm_vec3_dot(ba, ba);
	e2 = glm_vec3_dot(cb, cb);
	e3 = glm_vec3_dot(ca, ca);

	vec3 ae1, be2, ce3, ce1, ae2, be3;
	glm_vec3_scale(a, e1, ae1);
	glm_vec3_scale(b, e2, be2);
	glm_vec3_scale(c, e3, ce3);
	glm_vec3_scale(c, e1, ce1);
	glm_vec3_scale(a, e2, ae2);
	glm_vec3_scale(b, e3, be3);

	vec3 bad1, cbd2, cad3;
	glm_vec3_scale(ba, d1, bad1);
	glm_vec3_scale(cb, d2, cbd2);
	glm_vec3_scale(ca, d3, cad3);

	vec3 q1, q2, q3, qa, qb, qc;
	glm_vec3_sub(ae1, bad1, q1);
	glm_vec3_sub(be2, cbd2, q2);
	glm_vec3_sub(ce3, cad3, q3);
	glm_vec3_sub(ce1, q1, qa);
	glm_vec3_sub(ae2, q2, qb);
	glm_vec3_sub(be3, q3, qc);

	sep |= (glm_vec3_dot(q1, q1) > rr * e1 * e1) && (glm_vec3_dot(q1, qc) > 0);
	sep |= (glm_vec3_dot(q2, q2) > rr * e2 * e2) && (glm_vec3_dot(q2, qa) > 0);
	sep |= (glm_vec3_dot(q3, q3) > rr * e3 * e3) && (glm_vec3_dot(q3, qb) > 0);


	// Check if there is a collision, if so, then return from this function.
	return !sep;
}

bool SphereTriangleCollision(SphereCollider* s, Vertex vertices[3])
{
	// Check if there's a collision.
	if (!SphereTriangleColliding(s, vertices)) return false;

	// Now we resolve the collision.
	vec3 a;
	glm_vec3_sub(vertices[0].pos, s->pos, a);
	float dist = glm_vec3_dot(a, vertices[0].normal) - s->radius;

	vec3 n;

	glm_vec3_scale(vertices[0].normal, dist, n);
	glm_vec3_add(n, s->pos, s->pos);

	/*vec3 vel1, vel2;

	vec3 mul;
	glm_vec3_one(mul);
	vec3 nAbs;
	glm_vec3_abs(vertices[0].normal, nAbs);
	glm_vec3_sub(mul, nAbs, mul);
	glm_vec3_mul(s->velocity, mul, vel1);*/

	vec3 v;
	glm_vec3_one(v);
	glm_vec3_scale(v, glm_vec3_dot(s->velocity, vertices[0].normal), v);
	glm_vec3_mul(vertices[0].normal, v, v);
	glm_vec3_scale(v, 2 * s->bounciness, v);

	//glm_vec3_sub(s->velocity, v, vel2);
	glm_vec3_sub(s->velocity, v, s->velocity);
	
	//glm_vec3_lerp(vel1, vel2, s->bounciness, s->velocity);

	return true;
}

RaycastHit RayTriangleCollision(vec3 pos, vec3 dir, Vertex vertices[3])
{
	// Create 3 vectors to store the offset from the vertice's positions to the origin.
	vec3 a, b, c;
	glm_vec3_sub(vertices[0].pos, pos, a);
	glm_vec3_sub(vertices[1].pos, pos, b);
	glm_vec3_sub(vertices[2].pos, pos, c);

	// Create a basic raycast hit and set some basic variables.
	RaycastHit hit;
	hit.dist = 0.0f;
	glm_vec3_zero(hit.norm);
	glm_vec3_zero(hit.pos);

	// Step 1: finding P
	
	// check if ray and plane are parallel ?
	float NdotRayDirection = glm_vec3_dot(vertices[0].normal, dir);
	if (fabs(NdotRayDirection) < 0.01f) // almost 0 
		return hit; // they are parallel so they don't intersect ! 

	// compute d parameter using equation 2
	hit.dist = glm_vec3_dot(vertices[0].normal, a);

	// compute t (equation 3)
	float t = (glm_vec3_dot(vertices[0].normal, pos) + hit.dist) / NdotRayDirection; //printf("%f : %f, ", t, hit.dist);
	hit.dist = t; 
	//float t = hit.dist; 

	// check if the triangle is in behind the ray
	if (t < 0) return hit; // the triangle is behind 

	// compute the intersection point using equation 1
	vec3 P;
	glm_vec3_scale(dir, t, P);
	glm_vec3_copy(P, hit.pos);

	// Step 2: inside-outside test
	vec3 C0, C1, C2; // vectors perpendicular to triangle's plane 

	// edge 0
	vec3 edge0;
	glm_vec3_sub(b, a, edge0);
	vec3 vp0;
	glm_vec3_sub(P, a, vp0);
	glm_vec3_cross(edge0, vp0, C0); //printf("(%f, %f, %f) : (%f, %f, %f) = %f, ", C0[0], C0[1], C0[2], vertices[0].normal[0], vertices[0].normal[1], vertices[0].normal[2], glm_vec3_dot(vertices[0].normal, C0));
	if (glm_vec3_dot(vertices[0].normal, C0) < 0) return hit; // P is on the right side 

	// edge 1
	vec3 edge1;
	glm_vec3_sub(c, b, edge1);
	vec3 vp1;
	glm_vec3_sub(P, b, vp1);
	glm_vec3_cross(edge1, vp1, C1); //printf("(%f, %f, %f) : (%f, %f, %f) = %f, ", C1[0], C1[1], C1[2], vertices[0].normal[0], vertices[0].normal[1], vertices[0].normal[2], glm_vec3_dot(vertices[0].normal, C1));
	if (glm_vec3_dot(vertices[0].normal, C1) < 0) return hit; // P is on the right side 

	// edge 2
	vec3 edge2;
	glm_vec3_sub(a, c, edge2);
	vec3 vp2;
	glm_vec3_sub(P, c, vp2);
	glm_vec3_cross(edge2, vp2, C2); //printf("(%f, %f, %f) : (%f, %f, %f) = %f, ", C2[0], C2[1], C2[2], vertices[0].normal[0], vertices[0].normal[1], vertices[0].normal[2], glm_vec3_dot(vertices[0].normal, C2));
	if (glm_vec3_dot(vertices[0].normal, C2) < 0) return hit; // P is on the right side 


	//printf("\ng\n");
	glm_vec3_copy(vertices[0].normal, hit.norm);
	glm_vec3_scale(dir, hit.dist, hit.pos);
	glm_vec3_add(pos, hit.pos, hit.pos);
	return hit; // this ray hits the triangle
}

RaycastHit RaycastWorld(vec3 pos, vec3 dir, float dist, World world)
{
	RaycastHit hit;
	glm_vec3_zero(hit.pos);
	glm_vec3_zero(hit.norm);
	hit.dist = 9999.0f;
	vec3 rPos;
	glm_vec3_scale(pos, 1.0f / chunkWidth, rPos);

	float steps = max(max(fabsf(dir[0]), fabsf(dir[1])), fabsf(dir[2]));

	vec3 inc;
	glm_vec3_copy(dir, inc);
	glm_vec3_scale(inc, 1.0f / steps, inc);

	vec3 currentPos;
	glm_vec3_copy(rPos, currentPos);
	bool notHit = true;
	for (int i = 0; i < steps * dist && notHit; i++)
	{
		int x, y, z;
		x = (int)roundf(currentPos[0]);
		y = (int)roundf(currentPos[1]);
		z = (int)roundf(currentPos[2]);

		int16_t chunkIndex = -1;
		for (int i = 0; i < world.chunks.count; i++)
			chunkIndex = (glm_vec3_eqv((vec3) { x, y, z }, (vec3) { world.chunks.l[i].pos[0], world.chunks.l[i].pos[1], world.chunks.l[i].pos[2] }) ? i : chunkIndex);
		
		if (chunkIndex != -1)
		{
			for (uint16_t i = 0; i * 3 < FindVertexListListTotal(chunkIndex); i++)
			{
				RaycastHit newHit = RayTriangleCollision(pos, dir, &world.chunks.l[chunkIndex].verts.l[i * 3]);

				if (!glm_vec3_eqv((vec3) { 0.0f, 0.0f, 0.0f }, newHit.norm) && newHit.dist < hit.dist && newHit.dist < dist)
				{
					hit = newHit;
					notHit = false;
				}
			}
		}
		else
			break;

		glm_vec3_add(inc, currentPos, currentPos);
	}

	printf("\n(%f, %f, %f)\n", hit.pos[0], hit.pos[1], hit.pos[2]);

	return hit;
}