class ApplicationController < ActionController::Base
  	protect_from_forgery
  	before_filter :authorize, :except => [:index, :login, :register, :register_do]
  	filter_parameter_logging :password

  	private
  		def authorize
			logger.info 'in authorize'
			@user ||= session[:user] && User.find_by_name(session[:user])
			if @user.nil?
				session[:origin_url] = request.fullpath
				redirect_to :controller => :user, :action => :index
			end
		end			
	  
end
