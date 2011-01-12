class CreateAdminships < ActiveRecord::Migration
  def self.up
    create_table :adminships do |t|
      t.integer :group_id
      t.integer :user_id

      t.timestamps
    end
  end

  def self.down
    drop_table :adminships
  end
end
