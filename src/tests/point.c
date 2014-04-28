#include <math.h>
#include <glib.h>
#include <graphene.h>

static void
point_zero (void)
{
  const graphene_point_t *p;
  graphene_point_t q;

  p = graphene_point_zero ();
  g_assert_nonnull (p);
  g_assert_true (p == graphene_point_zero ());
  g_assert_cmpfloat (p->x, ==, 0.f);
  g_assert_cmpfloat (p->y, ==, 0.f);

  graphene_point_init_from_point (&q, graphene_point_zero ());
  g_assert_cmpfloat (q.x, ==, 0.f);
  g_assert_cmpfloat (q.y, ==, 0.f);
  g_assert_cmpfloat (graphene_point_distance (p, &q, NULL, NULL), ==, 0.f);
}

static void
point_init (void)
{
  graphene_point_t p, q;

  graphene_point_init (&p, 0.f, 0.f);
  g_assert_cmpfloat (p.x, ==, 0.f);
  g_assert_cmpfloat (p.y, ==, 0.f);

  graphene_point_init (&p, 1.f, 1.f);
  g_assert_cmpfloat (p.x, ==, 1.0f);
  g_assert_cmpfloat (p.y, ==, 1.0f);

  graphene_point_init_from_point (&q, &p);
  g_assert_cmpfloat (q.x, ==, p.x);
  g_assert_cmpfloat (q.y, ==, p.y);
}

static void
point_distance (void)
{
  graphene_point_t p, q;
  float x_d, y_d;

  graphene_point_init (&p, 0.f, 0.f);
  g_assert_cmpfloat (p.x, ==, 0.f);
  g_assert_cmpfloat (p.y, ==, 0.f);

  graphene_point_init (&q, 1.f, 1.f);
  g_assert_cmpfloat (q.x, ==, 1.0f);
  g_assert_cmpfloat (q.y, ==, 1.0f);

  x_d = y_d = 0.f;
  g_assert_cmpfloat (graphene_point_distance (&p, &q, &x_d, &y_d), ==, sqrtf (2.f));
  g_assert_cmpfloat (x_d, ==, 1.f);
  g_assert_cmpfloat (y_d, ==, 1.f);
}

static void
point_near (void)
{
  graphene_point_t p, q;

  graphene_point_init (&p, 0.f, 0.f);
  graphene_point_init (&q, 0.1f, 0.1f);

  g_assert_true (graphene_point_near (&p, &q, 0.2f));
  g_assert_false (graphene_point_near (&p, &q, 0.001f));
  g_assert_false (graphene_point_near (&p, &q, 0.f));
}

int
main (int argc, char *argv[])
{
  g_test_init (&argc, &argv, NULL);

  g_test_add_func ("/point/init", point_init);
  g_test_add_func ("/point/distance", point_distance);
  g_test_add_func ("/point/near", point_near);
  g_test_add_func ("/point/zero", point_zero);

  return g_test_run ();
}