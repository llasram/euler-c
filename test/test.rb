#! /usr/bin/env ruby

require 'test/unit'

class EulerTests < Test::Unit::TestCase
  def test_p001; assert_equal(233168, problem(1)); end
  def test_p002; assert_equal(4613732, problem(2)); end
  def test_p003; assert_equal(6857, problem(3)); end
  def test_p004; assert_equal(906609, problem(4)); end
  def test_p005; assert_equal(232792560, problem(5)); end
  def test_p006; assert_equal(25164150, problem(6)); end
  def test_p007; assert_equal(104743, problem(7)); end
  def test_p008; assert_equal(23514624000, problem(8)); end
  def test_p009; assert_equal(31875000, problem(9)); end
  def test_p010; assert_equal(142913828922, problem(10)); end
  def test_p011; assert_equal(70600674, problem(11)); end
  def test_p012; assert_equal(76576500, problem(12)); end
  def test_p013; assert_equal(5537376230, problem(13)); end
  def test_p014; assert_equal(837799, problem(14)); end
  def test_p015; assert_equal(137846528820, problem(15)); end
  def test_p016; assert_equal(1366, problem(16)); end
  def test_p017; assert_equal(21124, problem(17)); end
  def test_p018; assert_equal(1074, problem(18)); end
  def test_p019; assert_equal(171, problem(19)); end
  def test_p020; assert_equal(648, problem(20)); end

  protected
  def problem(n)
    %x{./src/p#{sprintf("%03d", n)}}.chomp.split(' = ')[1].to_i
  end
end
