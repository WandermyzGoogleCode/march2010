require 'test_helper'

class UserControllerTest < ActionController::TestCase
  test "should get index" do
    get :index
    assert_response :success
  end

  test "should get login" do
    get :login
    assert_response :success
  end

  test "should get logout" do
    get :logout
    assert_response :success
  end

  test "should get register" do
    get :register
    assert_response :success
  end

  test "should get passwd" do
    get :passwd
    assert_response :success
  end

end
