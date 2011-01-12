# Table schema: (name:string, identifier:string, extra_info:text creator_id:integer)
class Group < ActiveRecord::Base
  belongs_to :creator, :class_name => "User"
  has_many :membership, :dependent => :destroy
  has_many :adminship, :dependent => :destroy
  has_many :recommendation, :dependent => :destroy
end
