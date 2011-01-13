class ApplicationController < ActionController::Base
  	protect_from_forgery
  	before_filter :authorize, :except =>[:login_index, :login, :register, :register_do]
  	config.filter_parameters  :password
    layout 'home'
  	private
  		def authorize
			logger.info 'in authorize'
			@user = session[:user] 
			if @user.nil?
				session[:origin_url] = request.fullpath
				redirect_to :controller => :user, :action => :login_index
			end
		end			
	  
end
