class HomeController < ApplicationController
  def index
  	@page = "home-index"
    @user = session[:user]
  end

end
