class UserController < ApplicationController
  require 'md5'
  def index
    
  end
  
  def login
    username = (params[:user] || "")
    password = params[:password] || ""
    password = md5(password.to_s)
    session[:user] = nil
    userRecord = User.find_by_name(username) 
    
    if userRecord.nil?
      flash[:message] = 'User does not exist.'
      redirect_to :action => :index
    else
      if userRecord.password == password
        session[:user] = username
        redirect_to :controller => :home, :action => :index
      else
        flash[:message] = 'Password Wrong'
        redirect_to :action => :index
      end
    end
  end
  
  def logout
    reset_session
    flash[:message] = 'You have signed out'
    redirect_to :action => :index
  end
  
  def register
    
  end
  
  def register_do
    username = params[:name] || ""
    password = params[:passwd] || ""
    logger.info password
    password_repeat = params[:passwd_repeat] || ""
    email = params[:email] || ""
    mobile = params[:mobile] || ""
    extra = params[:extra]||""
    
    if params[:name] != '' and params[:password] == params[:password_repeat]
      User.create( :name => username, :password => md5(password), :email => email, :mobile => mobile, :extra => extra)
      flash[:message] = 'You have registed successfully.'
      redirect_to :action => :index
    else
      flash[:message] = 'Something wrong with your input.'
      redirect_to :action => :register
    end
  end
  
  def passwd
    
  end
  
  private
  def md5(pass)
    return MD5.hexdigest(pass)
  end
end
